PG_MODULE_MAGIC;

Datum repeat_materialize(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(repeat_materialize);

Datum
repeat_materialize(PG_FUNCTION_ARGS)
{
  
	ReturnSetInfo   *rsinfo = (ReturnSetInfo *) fcinfo->resultinfo;
	MemoryContext   per_query_ctx = rsinfo->econtext->ecxt_per_query_memory;
	MemoryContext   oldcontext = MemoryContextSwitchTo(per_query_ctx);
  Tuplestorestate *tupstore = tuplestore_begin_heap(true, false, work_mem);
	TupleDesc	      tupdesc;
	bool            nulls[] = {0};

	int32  object = PG_GETARG_INT32(0);
	uint32 times  = PG_GETARG_INT32(1);

	/* create a function context for cross-call persistence */
	if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE) {
		elog(ERROR, "function returning record called in context that cannot accept type record");
	}
	
	while ( times-- ) {
		Datum values[] = { Int32GetDatum(object) };
		tuplestore_putvalues(tupstore, tupdesc, values, nulls);
	}

	rsinfo->setResult = tupstore;
	rsinfo->returnMode = SFRM_Materialize;
	rsinfo->setDesc = tupdesc;

	tuplestore_donestoring(tupstore);
	MemoryContextSwitchTo(oldcontext);
	return (Datum) 0;

}
