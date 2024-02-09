# pipg-rpo

## Overview
PIPG for Renzedvous and Proximity Operations

We solve a nonconvex rendezvous problem, which is free final time, uses Clohessy-Wiltshire dynamics and an impulsive thrust model where the control input is an instantaneous change in velocity. 

The constraints are maximum speed, maximum control input, and spherical keepout zone. This problem is solved using Sequential Convex Programming (SCP) and uses ECOS and PIPG to solve the convex subproblems.

This code was developed for [this paper](https://arxiv.org/abs/2402.04561) which was presented at the 2024 AAS Rocky Mountain GN&C Conference. 

## Running Code
To run the nominal rendezvous example from the paper run the following command from the root directory after activating a Julia session

```
include("test/run_nominal.jl")
```

To run the monte carlo from the paper run the following

```
include("test/run_mc.jl")
```

## Citing

If you find this code or paper useful please cite the following

```
@inproceedings{chari2024spacecraft,
  author = {Chari, Govind M. and Behcet Acikmese},
  title = {Spacecraft Rendezvous Guidance via Factorization-Free Sequential Convex Programming using a First-Order Method},
  booktitle = {AAS Rocky Mountain Guidance, Navigation and Control Conference},
  year = {2024},
}
```
