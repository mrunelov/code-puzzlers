# -*- coding: utf-8 -*-

"""
@author: Martin Runelöv

Thursday Code Puzzler: Sum of Multiples
http://java.dzone.com/articles/thursday-code-puzzler-sum

Find the sum of all multiples of 3 and 5 under 1,000.

"""



def sum_of_multiples(i, c):
"""
Returns the sum of all multiples of the integer i up to the ceiling c

"""
    # The sum of the first n integers is n(n+1)/2
    return i*((c/i)*(c/i+1))/2


def total_sum_of_multiples(x,y,c):
"""
Returns the total sum of multiples for two integers x and y.
Their total sums are added, and then their product is subtracted to remove
duplicate multiples.

"""	

    return (sum_of_multiples(x,999) +
            sum_of_multiples(y,999) -
            sum_of_multiples(x*y,999))


# Print the answer. 233168
print ('Sum of multiples: ' + str(total_sum_of_multiples(3,5,999)))
