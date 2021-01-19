# Project Reach: SPARTAN Flight Software

<img src='reach_logo.png' alt='Project Reach Logo' width=300>

This repo contains the main flight software for Reach's Project SPARTAN, which includes the development and implementation of a module sensor driver library aimed to support future BruinSpace software development even beyond Project Reach.

As a whole, Project SPARTAN stands as a pathfinder mission to develop the foundational technologies for a modular rocket payload system. With SPARTAN, Reach aims to essentially create a "better CubeSat", providing the necessary support for a variety of smaller payloads while keeping true to the 3U CubeSat form factor.

Contents:

<!--ts-->
- [Requirements](#requirements)
- [Functionality](#functionality)
- [Cloning the Repository](#cloning-the-repository)
- [Pulling Remote Changes](#pulling-remote-changes)
- [Dependencies](#dependencies)
- [Building](#building)
- [High-level Overview of Code Base](#high-level-overview-of-code-base)
- [Making Changes](#making-changes)
- [Testing](#testing)
    - [Unit Tests](#unit-tests)
    - [System Tests](#unit-tests)
    - [Testing Methods](#testing-methods)
        - [Coverity](#coverity)
        - [Sanitizer](#sanitizer)
        - [Valgrind](#valgrind)
- [Key Resources](#key-resources)
- [Coding Conventions](#coding-conventions)
    - [Style](#style)
    - [Good Practices](#good-practices)
- [Flight Software](#flight-software)
- [Profiling](#profiling)
<!--te-->

## Requirements

With SPARTAN being a pathfinder mission, SPARTAN's requirements have remained internally-defined, being developed by Reach for Reach, while aiming to mimic space and aerospace industry practices: higher-level mission requirements flow down to lower-level system and eventually sub-system requirements.

SPARTAN's requirements (and related documents) can be found on the Bruin Space Google Drive:
- [SPARTAN's Requirements](https://docs.google.com/spreadsheets/d/1wmKbEzY1uAeAfpqEKVN9oGsLVN8LYr34lVoQ2MfMf6E/edit#gid=0)  - Rev. 2 (current)
- [SPARTAN Requirements' Revision Log](https://docs.google.com/document/d/1skJprpNjTTqWb_BPmjK8BKo9V3Uefr9hbAc0C5wijEY/edit)

Transitioning into the 2020-2021 academic year, the SPARTAN project received an extension from its originally-planned 2-year lifetime as well as a small update in requirements, primarily aiming to add a more-interesting payload element. This project extension has taken the name of **SPARTAN v1.1**. Refer to [SPARTAN v1.1's Mission Extension and Update Proposal](https://docs.google.com/document/d/1hyW6czCNw3PkcbieIdZ7UJdFXSi7TBaoCcG0RHrB790/edit) for more information.

**NOTE:** Although SPARTAN's overall requirements have been revised slightly following the Preliminary Design Review (PDR), the Software-specific requirements have been virtually untouched.

## Functionality

SPARTAN's sensor driver library provides users with the ability to easily collect and construct custom data products from any variety of the libraries' supported sensors.

SPARTAN's FSW takes advantage of this sensor driver library, serving to poll all available sensors, construct the user-defined data products, and format into data packets to send off to SPARTAN's communications sub-system for transmission to our ground station. 

Supporting future software development, SPARTAN's sensor driver library has been built to be modular, providing a well-defined infrastructure that allows a user to build support for a new sensor module without needing to modify the libraries' methods for performing data collection and data product construction.

For more information, refer to SPARTAN's design review slides, listed in the [Key Resources](#key-resources) section of this README.documentation.

## Cloning the Repository

In order to create a local copy of the SPARTAN repository, `clone` the repo (which will create a copy in your current directory):

    git clone https://github.com/Bruin-Spacecraft-Group/SPARTAN.git

## Pulling Remote Changes

In order to update your local environment of any remote changes made to the SPARTAN repository branches, you must `pull` them into your local copy (ensuring your terminal's current directory is within your local SPARTAN repo): 

    git pull

However, you must If you want to first check what changes are made were made before merging them into your local copy, we must first `fetch` them with:

    git fetch

Then we can `merge` them with:

    git merge

## Dependencies

The SPARTAN sensor driver library builds itself primarily on Intel's [MRAA library](https://iotdk.intel.com/docs/master/mraa/), a C/C++ skeleton library for low-level communication between hardware. 

**TODO: Complete this section, explaining how to install MRAA and other potential dependencies. Perhaps in the future we can have the dependencies installation process be done through a script.**

## Building

To build the SPARTAN FSW, run the `make` command with either the `default` target or no target as follows:

```shell
make
```

## High-level Overview of Code Base

**TODO: This will be completed once Issue #11 and #12 are closed and completed. Refer to the `SPARTAN Software Architecture` https://docs.google.com/document/d/1g_4Ltz6UaWXYKXc5a7wMcE85elGKah6o92g3qZhnzHk/edit# when making this section (this document is outdated with regards to the updates made to address Issue #11, but it still has relevant sections). As Issue #52 mentions, perhaps this section should refer to a document located in the `docs` subdirectory that is an updated version of the `SPARTAN Software Architecture` document linked previously. This should include a reference to the main documentation directories for Software, Structures, Electronics, Management, etc.**

## Making Changes

Committing directly to `master` is disabled. `master` is protected by GitHub. Changes are required to go through the pull request process to allow proper testing and reviews by SPARTAN's software development team to ensure accuracy and validity before merging.

Generally, changes and additions made to the repository involve some sort of feature request or bug fix outlined in a Github Issue, located in the Github Issues section. When you've decided to take on an Issue, assign yourself that issue (towards the right-hand side of the Github interface), and begin the following process:

- Create a branch. For temporary branches (for anything from individually-assigned feature requests to documentation-update branches), prefix it with your username (`username-branch-name`). This makes it easier to distinguish it from long-lived branches.
- Commit your changes in that branch (locally). Make sure to document your changes well within your commit messages (**This is important. ** This not only make it easier for other developers to understand your changes, but its also a good skill and practice to develop for industry!). Make sure to include tests (this is **important** and a necessary step for most modifications before being able to merge with `master`). For more information on tests, please refer to the below [Testing](#Testing) section.
- Publish your branch to the remote SPARTAN repository (`git push -u origin branch-name-here`). Any local changes that you commit to your branch must then be pushed to the remote branch via `git push`.
- Submit a Pull Request (typically from your branch to `master`). For uniformity, please use normal [sentence case](https://en.wikipedia.org/wiki/Letter_case#Sentence_case) for the title (and not title case). Please thoroughly describe the changes made in your Pull Request's description (**THIS IS IMPORTANT**).
- In the pull request description, add a sentence like "Closes #xxx." where "xxx" is the issue number of the issue that are are closing with your feature/fix. This makes GitHub automatically close the issue when the pull request is merged `master`. Include relevant comments (that may include source-code reference-links, diagrams, or screenshots!) that will help the reviewer understand your change.

**NOTE:** For any large code formatting changes, please submit them as separate pull requests from functional changes. Although these large code formatting changes will be rare, keeping stylistic changes separate from functional changes will make it easier for peers to review the changes.

## Testing

**TODO: Will be implemented. Need to add testing infrastructure to support what is described here. This will be addressed by Issue #17.**

To run the tests:

    make test

To keep the output files around for each system test:

    SPARTAN_KEEP=x make test

To run a single system test:

    ./scripts/run-one-test test/system_tests/test_name_here

To run a single system test with GDB:

    SPARTAN_GDB=x ./scripts/run-one-test test/system_tests/test_name_here

To run a single system test with Valgrind:

    SPARTAN_VALGRIND=x ./scripts/run-one-test test/system_tests/test_name_here

### Unit Tests

**TODO: Will be implemented.**

### System Tests

**TODO: Will be implemented.**

System tests are in `test/system_tests`. Each directory in there requires files X, Y, and Z:

- `X`: description
- `Y`: description
- `Z`: description

The system test script will launch `build/spartan` and run it against ...

### Testing Methods

**TODO: Will be implemented. This is a sample list of some popular testing tools/methods that would be great to use.**

#### Coverity

Coverity is static analysis tool. It detects bugs at compile-time. Some of its
messages are somewhat stylistic and won't necessarily cause problems. Some
examples of this would be:

- **Warnings about stack space usage.** By default it encourages the developer
  not to put more than 10000 bytes on the stack for a single variable. More
  would typically be fine on the platforms we support. But best practice would
  be to put such large variables on the heap to avoid risk of a stack overflow.
- **Unused includes.** It is good practice to avoid including header files that
  are not needed. Note that is also good practice to make sure to include
  header files that you *do* need (and not rely on indirect header includes).
  Coverity will not warn about this latter case.

Other messages must be fixed. Some examples of this would be:

- Anything that mentions an "overrun".
- Anything that mentions uninitialized variables.

#### Sanitizer

AddressSanitizer detects memory bugs at runtime. It is like Valgrind, but is an order of magnitude faster via compile-time instrumentation. Additionally, unlike Valgrind it can detect stack memory errors, which Valgrind does not. It does not detect uninitialized memory usage though.

See the [Sanitizer wiki](https://github.com/google/sanitizers/wiki/AddressSanitizer) for details.

#### Valgrind

Valgrind is a tool that checks for heap memory errors, uninitialized memory, and memory leaks. It instruments the SPARTAN FSW at runtime and reports error messages as tests run.

The Valgrind (Memcheck) [quick start guide](http://valgrind.org/docs/manual/quick-start.html) describes how to interpret Valgrind's error messages.


## Key Resources

- [Preliminary Design Review (PDR)](https://docs.google.com/presentation/d/1Ni4MBcuMXI3R2DlnYgesK2rmyYDbXoLMQEeCFVjE51U/edit#slide=id.g25d2e80a4c_0_0)
- [Critical Design Review (CDR)](https://docs.google.com/presentation/d/1yBN_zy_TYX6eWVL2albne1UNs3u9UPI5ePQl-ad72SY/edit#slide=id.g7c4f7d256d_3_4)
- [SPARTAN v1.1 Project Extension and Update Proposal](https://docs.google.com/document/d/1hyW6czCNw3PkcbieIdZ7UJdFXSi7TBaoCcG0RHrB790/edit) (for 2020-2021 academic year)

## Coding Conventions

We want our style to be consistent throughout the SPARTAN code, ensuring good code readability and understandability without ambiguity.

The code base uses C++11 for C++ code.

### Style

- Within Source Code
    - 4 space indentation in source code, not tabs (except where necessary, i.e. standard Makefiles).
    - `under_scores` with all lowercase for variable and function names.
    - `PascalCase` for class names.
    - `lowercase` for namespaces. Namespaces should be short names.
    - Allman-style brackets.
    - 2 empty lines between functions.
    - Library and header includes are grouped as local, third-party, then standard library. Within a group they are in alphabetical order. This makes it more likely we will detect if our local header files themselves are missing necessary includes.
    - When including sibling header files, use the `"header_here.h"`. Otherwise, use the `<header_here.h>` form.
- Directory-Level
    - `under_scores` with extension (`.c`, `.cpp`, etc.) for source code files.
    - `dashes-between-words` for executables (including scripts).
    - `hyphenated-words` for public-facing things like repository names and public-facing binaries/scripts. This conforms to the common convention for things like Unix program names and GitHub repository names.
    - Prefer flat organizations for file structures as much as possible.

### Good Practices

Although these aren't "mandatory," try to develop all source code with these in mind as if they are.

- Non-member functions preferred over member functions unless the latter adds value. See [Meyers](http://www.drdobbs.com/cpp/how-non-member-functions-improve-encapsu/184401197).
- Fix all compiler warnings. **TODO: Look into turning warnings into errors automatically for GCC.**
- Write helpful Git commit messages with the [standard style](https://chris.beams.io/posts/git-commit/).
- Label fix-me and to-do notes in the form `TODO(username): Sentence here.` or `FIXME(username): Sentence here.` to indicate who needs to/will deal with the note eventually.
- Avoid unnecessary duplication. If a large amount of code is used in many places, make it a function.
- Make variables/parameters `const` where possible to make it clear they won't change.

## Profiling

**TODO: Will be implemented. This would be a nice feature to implement down the road. Some ideas for profiling tools include gprof, valgrind, gperftools. We should have this profiler run via `make profile` of some sort.**