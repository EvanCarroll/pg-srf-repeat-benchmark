Datum repeat_valuepercall(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(repeat_valuepercall);

typedef struct
{
	Datum  object;
	uint32 times;
} repeat_valuepercall_fctx;

Datum
repeat_valuepercall(PG_FUNCTION_ARGS)
{

	if (SRF_IS_FIRSTCALL())
	{
		int32 object = PG_GETARG_INT32(0);
		int32 times  = PG_GETARG_INT32(1);

		FuncCallContext *funcctx = SRF_FIRSTCALL_INIT();
		MemoryContext oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);
		repeat_valuepercall_fctx *fctx = (repeat_valuepercall_fctx *) palloc(sizeof(repeat_valuepercall_fctx));

		fctx->times  = times;
		fctx->object = Int32GetDatum(object);

		funcctx->user_fctx = fctx;
		MemoryContextSwitchTo(oldcontext);
	}

	FuncCallContext *funcctx        = SRF_PERCALL_SETUP();
	repeat_valuepercall_fctx *fctx  = funcctx->user_fctx;

	if ( (fctx->times)-- > 0 ) {
		SRF_RETURN_NEXT(funcctx, fctx->object);
	}
	else {
		SRF_RETURN_DONE(funcctx);
	}
}
