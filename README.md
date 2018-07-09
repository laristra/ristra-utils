# Ristra Utils Library

The Ristra Utils project provides I/O and other low-level utilities for the
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

# Copyright

Copyright (c) 2016, Los Alamos National Security, LLC
All rights reserved.

Copyright 2016. Los Alamos National Security, LLC. This software was produced under U.S. Government contract DE-AC52-06NA25396 for Los Alamos National Laboratory (LANL), which is operated by Los Alamos National Security, LLC for the U.S. Department of Energy. The U.S. Government has rights to use, reproduce, and distribute this software.  NEITHER THE GOVERNMENT NOR LOS ALAMOS NATIONAL SECURITY, LLC MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LIABILITY FOR THE USE OF THIS SOFTWARE.  If software is modified to produce derivative works, such modified software should be clearly marked, so as not to confuse it with the version available from LANL.

Additionally, redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of Los Alamos National Security, LLC, Los Alamos National Laboratory, LANL, the U.S. Government, nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY LOS ALAMOS NATIONAL SECURITY, LLC AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL LOS ALAMOS NATIONAL SECURITY, LLC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

<!-- vim: set tabstop=2 shiftwidth=2 expandtab fo=cqt tw=72 : -->
