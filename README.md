# Ristra Low-Level (RistraLL) Library

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

# Notes on File Scope Operations

The requirement that registrations happend at file scope should be fine
because we are unlikely to call I/O operations from somewhere other than
the *top-level task*. This is especially true with control replication
in Legion. This does not imply that I/O callback functions cannot invoke
tasks, it just means that they cannot be tasks themselves. Once inside
of a callback, the user may access data through a runtime, or that is
globally available, to invoke a set of tasks to carry out the actual I/O
operations through calls to the abstract interface. This is consistent
with the FleCSI model, because it assumes that data must first be mapped
into a task before they are accessible by the user. Additionally, once
inside of a task execution, the user can depend on certain operations
being available, although it may be neccessary to define a special I/O
task type to insure this.

For an initial example of the registry, look at
'ristrall/io/test/registry.cc'. This file shows the basic registration
of a set of I/O functions, which are then invoked through the runtime.
Although currently incomplete, 'ristrall/io/interface.h' demonstrates
the policy-based structure that can be used to select different backend
implementations. Logic is already included for HDF5.

<!-- vim: set tabstop=2 shiftwidth=2 expandtab fo=cqt tw=72 : -->
