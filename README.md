# Publisher-Subscriber

1. Publisher-Subscriber design and it's extensibiliy.

Problem: Usually in one-to-many relationships of components, change in one component requires change in other associated components if they are tightly coupled.

Solution: A Publisher-Subscriber type of design reduces such dependency between components by introducing loose coupling. 
- This program implements a Push model where a Publisher notify it's subscribers about the changes at it's end along with required data. 
- Main points covered in this program are Publisher-Subscriber design and it's extensibility. new Subscribers can easily inherit and start listening for notifications.
- Irrespective of how many and who are it's subscribers, Publisher notify those. 
- The Publisher subclass reads different component files and calculates the cost of that component. It then notify registered Subscribers parallely (using threads)
  when all components are loaded or single component info gets updated.



2. What it doesn't address.
- The main test program leveraging the design is not robust to deal with all possible user inputs.
- In implementation of Publisher subclass, discovering different component files and reading those files is not hardened to address 
  all possibilities or error scenarios as directory/files with no permissions or non-existent directory path as input.
- In implementation of Subscriber subclasses (*Chart), the data received through update method is only printed on console and not really used to draw some chart.
  Due to the shared "cout" object in same address space, console output printed by Subscriber subclasses is garbled and appears in any sequence. Subscriber subclasses need
  to use some locking/sharing mechanism to use shared resources in racing threads.


  
3. In case the executable doesn't run on your system, then please recompile the source with latest c++ version (min version -std=c++11)
   make
