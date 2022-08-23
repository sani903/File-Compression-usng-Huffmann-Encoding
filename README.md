# File Compressor using the Huffman Coding Algorithm:


## Problem:

- Data storage is one of the most cruicial aspects of all the electronic devices in use today.

- Given how every device has a finite storage capacity, this limits the amount of data a user can store.

- Using the Huffman Coding Algorithm, we have programmed a Text File Compressor.

- The programme will take input text from the user and compress it.

- Compressing will allow us to store the same input text in a lesser space by utilising various data structures while ensuring data integrity.

- Upon decompression, the encoded user data will be displayed as the original text and also show the % space saved by the user after compression.

<br>

## Output:

<img src="https://drive.google.com/uc?export=view&id=14maa2FwfJQKrvE2I4p2_QKtz9eGpCxeV" />

<br>

## Data Structures Used:

1. Priority Queue

2. Unordered Map

3. Vector

4. Binary Heap

<br>

## Steps:

1. Get the frequency of each character from the input text

2. Build Huffman Tree and assign the binary code to each character

3. *Compression*: Encode each character of the input text with the binary code

4. *Decompression*: Decode by replacing each binary code with the associated character

<br>

- Unordered Maps from the STL are utilised in storing the characters and their frequencies

- Priority queue is crucial while generating the Huffman Tree as the algorithm depends on the priority order of the characters

- Vectors from the STL are required to keep track of nodes and assist the priority queue

