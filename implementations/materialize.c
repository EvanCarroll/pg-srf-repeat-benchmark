Datum repeat_materialize(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(repeat_materialize);

Datum
repeat_materialize(PG_FUNCTION_ARGS)
{
  
	ReturnSetInfo   *rsinfo       = (ReturnSetInfo *) fcinfo->resultinfo;
	rsinfo->returnMode = SFRM_Materialize;

	MemoryContext   per_query_ctx = rsinfo->econtext->ecxt_per_query_memory;
	MemoryContext   oldcontext    = MemoryContextSwitchTo(per_query_ctx);

	Tuplestorestate *tupstore     = tuplestore_begin_heap(false, false, work_mem);
	rsinfo->setResult = tupstore;
	
	TupleDesc	      tupdesc = rsinfo->expectedDesc;
	//rsinfo->setDesc = rsinfo->expectedDesc;

	bool            nulls[1] = {0};

	int32  object = PG_GETARG_INT32(0);
	uint32 times  = PG_GETARG_INT32(1);

	Datum values[1] = { Int32GetDatum(object) };

	while ( times-- ) {
		tuplestore_putvalues(tupstore, tupdesc, values, nulls);
	}

	tuplestore_donestoring(tupstore);
	MemoryContextSwitchTo(oldcontext);
	return (Datum) 0;

}
