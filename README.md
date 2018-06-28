# The robber problem

A robber want’s to rob the bank. The bank has n vaults, arranged as a circle. Each of them has varying amount of money in it. The robber’s goal is to steal the maximum amount of money from the vaults. But the bank’s alarm system won’t make it easy for the robber. The alarm system turns on if the robber steals from more than two vaults, within a set of five consecutive vaults. For example, let the following series of numbers represent the amount of money in each of the vaults:134, 1, 2, 3, 1234, 4, 6, 7, 8, 345, 677, 45, 78, 1, 9. 


The first vault contains 134 Rs, the second vault contains 1 Rs and so on.  Note that the 15th vault (the final one which has 9 Rs in it) is adjacent to the first vault which contains 134 Rs, as the vaults are placed in a circular order. Thus, if the thief steals from just the first vault and the second vault, he would get away with the money he stole. Because, you cannot form a set of consecutive five vaults among which more than two are stolen from. But if the first, the second and the third vaults are stolen from, then it is possible to form multiple consecutive sets of five vaults which has more than two of its vaults which are robbed. Example of sets (the numbers represent the vault number and not the money in it): 1,2,3,4,5. In this set, we have the following vaults from which the money is stole from: 1, 2,3. This exceeds the limit, thus the alarm will turn on and the thief will get caught. Even if you consider the set: 15, 1, 2, 3, 4, the vaults 1,2 and 3 are present, which the thief robbed from. Thus, the alarm will go on, and the thief will get caught.  

Another example will be, the vaults: 1,3, 7, 12 are stolen from. Though this may not be the best possible solution, for maximizing the total amount stole, the alarm won’t turn on. This is because, it is not possible to form a consecutive set of five, such that the set contains more than one vault from which the money is stolen from. Example: the set of vaults, 1, 2, 3, 4, 5, contains just two vaults which are stole from and the set of vaults, 4, 5, 6, 7, 8, contains just one vault which is stolen from and so on. You must test this by trying out all the possible sets of 5 consecutive vaults that can be formed, and none of them must contain more than two vaults that are stolen from. Else, the thief will get caught. The problem is to maximize the amount of money stolen by the thief, and also ensuring that the thief does not get caught in the event. 

Given parameters:-

-The number of vaults: n
-The amount of money in each vault.

To solve: 
 maximize the amount of money that will be stolen without triggering the alarm.

The range of n: 1 to 100

**About this question:** *My placement teacher gave me this problem, and it took me 6 to 7 hours to solve it. I would have solved it a lot faster if I had understood the question correctly, when he first told me. I was solving a more complicated problem, until I reported my states to him, and it was when I realized that I had been solving an entirely different problem. Fortunately, it had a similar approach and I didn’t have to toss away any code as a result. By the way, my placement teacher classified this question as hard.*

**Note:** *My solution, which is in main.cc file, does not provide the correct result if the number of vaults are less than 5. It is a unique corner case which can be easily handled and I ignored it out of laziness*
