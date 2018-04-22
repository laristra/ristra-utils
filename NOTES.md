# Development Notes

As a general note, the current code provides a structure for a tool that
can probably work for checkpoint/restart and other I/O operations.
However, it should not be taken as a literal implementation. It
***will*** be necessary to make changes to the interface. Do not
hesitate to make these changes, and do not try to preserve the current
interface or structure where it does not make sense.

* We may need to add some explicit ordering information, e.g., certain
  targets may need to be loaded before others.
* The return type for registry functions is problematic. What do we do
  if one fails? This could be a partial failure, which could leave the
  system in an invalid state.

<!-- vim: set tabstop=2 shiftwidth=2 expandtab fo=cqt tw=72 : -->
