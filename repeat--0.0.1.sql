-- CREATE FUNCTION repeat_valuepercall(n int4, m int4)
-- RETURNS SETOF int4
-- AS 'MODULE_PATHNAME', 'repeat_valuepercall'
-- LANGUAGE C STRICT VOLATILE;

-- CREATE FUNCTION repeat_materialize(n int4, m int4 )
-- RETURNS TABLE(repeat int4)
-- AS 'MODULE_PATHNAME', 'repeat_materialize'
-- LANGUAGE C STRICT VOLATILE;

-- CREATE FUNCTION repeat_materialize(n int4, m int4 )
-- RETURNS SETOF RECORD
-- AS 'MODULE_PATHNAME', 'repeat_materialize'
-- LANGUAGE C STRICT VOLATILE;

CREATE FUNCTION repeat_materialize(n int4, m int4 )
RETURNS TABLE(x int4)
AS 'MODULE_PATHNAME', 'repeat_materialize'
LANGUAGE C STRICT VOLATILE;

