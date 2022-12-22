# RSMT
# rectilinear steiner minimum tree
the algorithm used:|
|A Sequential Steiner Tree Heuristic|
1.Find the closest (in terms of rectilinear distance) pin pair, |
construct their minimum bounding box (MBB) |
2.Find the closest point pair (pMBB,pC) between any point pMBB on |
the MBB and pC from the set of pins to consider |
3.Construct the MBB of pMBB and pC|
4.Add the L-shape that pMBB lies on to T (deleting the other L- shape). |
If pMBB is a pin, then add any L-shape of the MBB to T. |
5.Go to step 2 until the set of pins to consider is empty|
Testcases format: ICCAD 201|
##########################
• input:|
•  Net <net_id> <num_pins>|
•  0 <x_coordinate> <y_coordinate>|
•  …
•  <num_pins - 1> <x_coordinate> <y_coordinate>|
• Output:|
•  Steiner points lists <x_coordinate> <y_coordinate|
•  Edge lists <x1> <y1> <x2> <y2>
• Evaluation:
•  Wirelength
•  Runtime 
• Submissions:
•  The outputs
•  Code with Doc (Please make sure your code can reproduce your results. You could specify the 
hyperparameters and seeds in the Doc. We will run your code and to check the output.)



git clone XXXX
./runme.sh
Type into “2_50”, ”3_100”, “4_150”, “5_200”
You will get similar two files.
The output is two files:
(1):1_10_steiners : the list of steiner points in the RSMT
(2):1_10_edges:the list of the edges of the RSMT
