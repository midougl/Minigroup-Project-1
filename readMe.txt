Group A - CS4323 Mini Group Project

Progress Report ReadMe

To run the client/server, have 2-3 seperate csx windows running on the same server (csx1 for example) and have both be
in the folder with both the client.c file and Game_Server file. have one run the Game_Server file by compiling with
"gcc Game_Server.c -o server" and then type "./server" (this calls the output file that you just made)j. Then leave that up
and go to one of the seperate windows. Type in "gcc client -o client" to compile the client file then type "./client"
to run the client output. The client should be connected with that server program. You can try this with another csx server window.
Should be able to send messages to the server with the server sending back to the client the same message (for testing).
Need to change the messaging system to posix message passing, and haven't been able to load the game into the server due to this

If wanting to test the game seperately, make sure word_game file is located in folder with all input.txt files, dictionary.txt, and all needed
.h files. Compile the word game the same way as the game_server or client. Game should be able to run. There's still bugs that need to be fixed 
(keep previous words, check if player used needed word length, etc) but the structure is there.
