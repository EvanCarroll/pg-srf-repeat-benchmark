Datum repeat_materialize(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(repeat_materialize_preferred);

typedef struct
{
	Datum  object;
	uint32 times;
} repeat_materialize_preferred_fctx;

Datum
repeat_materialize_preferred(PG_FUNCTION_ARGS)
{
  
	//rsinfo->setDesc = rsinfo->expectedDesc;

	// if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE) {
	// 	ereport(
	// 			ERROR,
	// 			errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
	// 			errmsg("function returning record called in context that cannot accept type record")
	// 	);
	// }
	
	int32  object = PG_GETARG_INT32(0);
	uint32 times  = PG_GETARG_INT32(1);
	
	if (SRF_IS_FIRSTCALL())
	{
		ReturnSetInfo   *rsinfo       = (ReturnSetInfo *) fcinfo->resultinfo;

		// If we prefer materialize, get it done
		if ( rsinfo->allowedModes & SFRM_Materialize_Preferred ) {

			MemoryContext   per_query_ctx = rsinfo->econtext->ecxt_per_query_memory;
			MemoryContext   oldcontext    = MemoryContextSwitchTo(per_query_ctx);

			Tuplestorestate *tupstore     = tuplestore_begin_heap(false, false, work_mem);
			rsinfo->setResult             = tupstore;
			rsinfo->returnMode            = SFRM_Materialize;
	
			TupleDesc	tupdesc = rsinfo->expectedDesc;

			Datum values[1]             = { Int32GetDatum(object) };
			bool  nulls[sizeof(values)] = {0};

			while ( times-- ) {
				tuplestore_putvalues(tupstore, tupdesc, values, nulls);
			}

			tuplestore_donestoring(tupstore);
			MemoryContextSwitchTo(oldcontext);
	
			PG_RETURN_NULL();
		}

		// Initialize for multicall
		else {
			FuncCallContext *funcctx = SRF_FIRSTCALL_INIT();
			MemoryContext oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);
			repeat_materialize_preferred_fctx *fctx = (repeat_materialize_preferred_fctx *) palloc(sizeof(repeat_materialize_preferred_fctx));

			fctx->times  = times;
			fctx->object = Int32GetDatum(object);

			funcctx->user_fctx = fctx;
			MemoryContextSwitchTo(oldcontext);
		}

	}
	
	FuncCallContext *funcctx                = SRF_PERCALL_SETUP();
	repeat_materialize_preferred_fctx *fctx = funcctx->user_fctx;

	if ( (fctx->times)-- > 0 ) {
		SRF_RETURN_NEXT(funcctx, fctx->object);
	}
	else {
		SRF_RETURN_DONE(funcctx);
	}

}
