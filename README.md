# _K_-Dimensional Tree

This repository contains a simple C++ implementation of a [_k_-d Tree](https://en.wikipedia.org/wiki/_k_-d_tree)

<p style="color: rgb(237, 108, 2); background-color: rgb(255, 244, 229); padding: 12px; border-radius: 6px;">This repo is for educational purpose only, <b>DON'T</b> use it in production</p>

## Supported operations

- [x] Add _k_-dimensional point
- [x] Delete _k_-dimensional point via _soft-delete_
- [x] Query _k_-dimensional point
- [x] (_circular_) Range query on a _k_-dimensional point 
- [x] Pretty print _k_-d Tree

## Getting started

### Prerequisites

In order to run the project you need

- **g++** compiler
- [**CMake**](https://cmake.org/)

If you have [Docker](https://docs.docker.com/engine/install/) installed on your machine you can run the project using the [development container]((https://containers.dev/) ) located in the `.devcontainer` folder.

### Installation

```bash
make clean
make
```

### Usage

```
./bin/kd-tree
```

## Roadmap

- [ ] Tree rebalancing
- [ ] Pretty print with indentation
- [ ] Python interface

## License
Distributed under the MIT License. See LICENSE.txt for more information.

## Contact

Alessio Narder - <a href="mailto:alessio.narder@gmail.com">alessio.narder@gmail.com</a>