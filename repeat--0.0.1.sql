CREATE FUNCTION repeat_valuepercall(n int4, m int4)
RETURNS SETOF int4
AS 'MODULE_PATHNAME', 'repeat_valuepercall'
LANGUAGE C STRICT VOLATILE;

CREATE FUNCTION repeat_materialize(IN object int4, IN times int4)
RETURNS TABLE(x int)
AS 'MODULE_PATHNAME', 'repeat_materialize'
LANGUAGE C STRICT VOLATILE;

