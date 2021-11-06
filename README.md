PostgreSQL Set-Returning-Function (SRF) C-Extension Benchmarks
====

This repo consists of multiple implementations of a simple SRF that repeats it
input.

    repeat_implementation( what int4, row_count int4 )

The output of this function is a set of `row_count` rows of int4 columns that
just repeat `what`.

Implementations
====

There are three current implementations both with the same signature described above.

* [`repeat_materialize`](./implementations/materialize.c) (`SRFM_Materialize`)
* [`repeat_valuepercall`](./implementations/valuepercall.c) (`SRFM_ValuePerCall`)
* [`repeat_materialize_preferred`](implementations/materialize_preferred.c) (`SFRM_Materialize_Preferred`)

Raison d'être
====

This exists because the [doc says,](https://www.postgresql.org/docs/current/xfunc-c.html)

> C-language functions have two options for returning sets (multiple rows). In
> one method, called **`ValuePerCall`** mode, a set-returning function is called
> repeatedly (passing the same arguments each time) and it returns one new row
> on each call, until it has no more rows to return and signals that by
> returning NULL. The set-returning function (SRF) must therefore save enough
> state across calls to remember what it was doing and return the correct next
> item on each call. In the other method, called **`Materialize`** mode, an SRF fills
> and returns a tuplestore object containing its entire result; then only one
> call occurs for the whole result, and no inter-call state is needed.

[I asked under which case would the performance of one be greater than the
other.](https://dba.stackexchange.com/q/301920/2639) There was almost no
documentation advising one or the other for performance, so I created this repo
to help understand the call-convention overhead of these two methods.


Research
====

* [`src/backend/utils/fmgr/README`](https://github.com/postgres/postgres/blob/master/src/backend/utils/fmgr/README)

Patches Accepted
====

Please open up issues if any of these examples can be reduced in complexity or
made more performant.

**Idiot disclaimer: I really don't have any idea what I'm doing.**
