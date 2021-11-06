CREATE FUNCTION repeat_valuepercall(object int4, times int4)
RETURNS TABLE(repeat int4)
AS 'MODULE_PATHNAME', 'repeat_valuepercall'
LANGUAGE C STRICT VOLATILE;

CREATE FUNCTION repeat_materialize(object int4, times int4)
RETURNS TABLE(repeat int4)
AS 'MODULE_PATHNAME', 'repeat_materialize'
LANGUAGE C STRICT VOLATILE;

CREATE FUNCTION repeat_materialize_preferred(object int4, times int4)
RETURNS TABLE(repeat int4)
AS 'MODULE_PATHNAME', 'repeat_materialize_preferred'
LANGUAGE C STRICT VOLATILE;
