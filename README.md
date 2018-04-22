# Ristra Low-Level Library (RistraLL)

The RistraLL project provides I/O and other low-level utilities for the
Ristra project.

# I/O Model

The RistraLL I/O interface provides a mechanism for the various
components of a Ristra-based project to register as participants for
simulation I/O operations, e.g., checkpoint/restart, analysis, and other
operations. Additionally, RistraLL I/O provides an abstract interface
for reading and writing to a hierarchical data store format. For
clarity, the I/O model has two components: 1) A registry that allows
each component to specify a set of callback functions for the supported
operations of the I/O system, and 2) An abstract, low-level I/O
interface that can be used to interact with the opaque data store.

* **Registry**<br>
  The registry is implemented as a singleton object with registration at
  file scope. Component functions must therefore be defined as static
  functions. This assumes that any state accessed by the I/O function is
  accessible through another runtime, e.g., FleCSI.

* **Interface**<br>
  The I/O interface abstracts basic interactions with a data store
  object. The interface uses a policy-based design, such that different
  backend implementations can be employed.

<!-- vim: set tabstop=2 shiftwidth=2 expandtab fo=cqt tw=72 : -->
