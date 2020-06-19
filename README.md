# IOTResearch
An demo of the minimizationc of power comsumption of IoT edge devices inspired by DREAM architecture.
Important:
Videos folder under client has  10 videos, and they are huge. You do not have to download it. Just download the rest, create a Videos folder in client, and run createFiles.exe

Update: A draft of ED protocol is written with asusmption of > O(n) tasks.
Version 1.0
1. Current assumptions: all delay are 10 seconds, files are randomly centered at 6.25M. Complexity is all 2. Spawn every 10 seconds per client. Server has 500M/s processing speed, and it is not actually doing the processing, just sleeping.
2. Completed work: now the server handles communication with multiple clients corectly using socket. Server correctly handles queue and time. Client will decidewhether offload or not using response from server.
TODO:
1. Implement actual workload for client. (Using nested for loops)
2. If step 1 causes bugs on sleep in thread, switching to posix timer.
