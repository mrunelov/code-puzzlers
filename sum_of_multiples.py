# Find all the sum of all multiples of 3 and 5 under 1,000

# Fast math version:

# Returns the sum of all multiples of the integer i up to the ceiling c
def sum_of_multiples(i, c):
    # The sum of the first n integers is n(n+1)/2
    return i*((c/i)*(c/i+1))/2

# Returns the total sum of multiples for two integers.
# Their total sums are added, and then their product is subtracted to remove
# duplicate multiples.
def total_sum_of_multiples(x,y,c):
    return (sum_of_multiples(x,999) +
            sum_of_multiples(y,999) -
            sum_of_multiples(x*y,999))

# Print the answer. 233168
print total_sum_of_multiples(3,5,999)
