# pipg-rpo
PIPG for Renzedvous and Proximity Operations

The `convex/` directory solves a convex rendezvous problem. This problem is fixed final time, uses Clohessy-Wiltshire dynamics and an impulsive thrust model where the control input is an instantaneous change in velocity. The constraints are a maximum speed, maximum control input, and an approach cone. This problem is solved using YALMIP/ECOS and PIPG.

The `ptr/` directory solves a nonconvex rendezvous problem. This problem is free final time, uses Clohessy-Wiltshire dynamics and an impulsive thrust model where the control input is an instantaneous change in velocity. The constraints are maximum speed, maximum control input, and spherical keepout zone. This problem is solved using Sequential Convex Programming (SCP) and uses ECOS and PIPG to solve the convex subproblems.
