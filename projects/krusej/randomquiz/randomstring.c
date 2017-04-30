/*

The first step was to tackle what inputChar() needed to do. Initially, I was going to include all possible characters,
but that didn't seem necessary since there were only 9 different characters that mattered for testme(). So, I limited
the randomness to only those 9 characters, but in any order. I used an array to store the 9 different integer values for
characters (decimal ASCII values). The randomness is selecting a random number from 0 to 8, then returned that element
of the array.

Next, for inputString(), I had planned on using inputChar() as the function to create random characters for the string,
but then I limited the characters in inputChar. Instead, I recreated some of the random code from inputChar(), stuck in
a for loop from i = 0 to 4, had it select between ASCII characters 97-122, and placed those characters in s[i]. The last
character in the string (s[5]) is set to null.

Initially, I was going to include null as an option for any of the 6 characters in the random string, but it ran for so
long that my connection with the engr server was terminated. The following is the result:

Iteration 1062866: c = (, s = reset, state = 9

*/
