# RandomWalk

- Transfer the code to CUDA
   * Issues:
      - Code does not work for large 'R' (Max test-value of R = 700)
      - Error % lies between 10% to 25%, which is too high, as compared to serial processing.
      - Wait for fixes. These issues are linked to the implementation of the curand() functions.
    
- Obtain a larger dataset.

- Then, tweak the theoretical model, if necessary.


P.S. This code is in no way meant to be used in any kind of serious/production work, at least, not in its current state.
