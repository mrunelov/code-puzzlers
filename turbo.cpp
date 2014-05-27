/*
 * Turbo
 * https://kth.kattis.scrool.se/problems/turbo
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <cstring>

#define MAX 100000

int n;
int numbers[MAX+1];
int position[MAX+1];

/* fenwick tree */
struct fenwick {
   int a[MAX+1];

   fenwick() {
      memset( a, 0, sizeof a );
   }

   int query( int X ) {
      int ret = 0;
      for( int x = X; x > 0; x -= x&-x ) {
         // printf("a[%d] = %d \n", x, a[x]);
         ret += a[x];
      }
      return ret;
   }

   int sum( int lo, int hi ) {
      return query( hi ) - query( lo-1 );
   }
   
   void add( int X, int val ) {
      // printf("Add called with %d and %d\n", X, val);
      for( int x = X; x <= n; x += x&-x ) {
         a[x] += val;
         // printf("tree[%d] += %d\n", x, val);
         // printf("tree[%d] = %d\n", x, a[x]);
      }
      // printf("\n");
   }
} alive;

int main( void ) {
   
   scanf( "%d", &n );
   for( int i = 1; i <= n; ++i ) {
      scanf( "%d", &numbers[i] );
      position[numbers[i]] = i;
      // printf("P[%d] = %d\n", numbers[i], i);
      alive.add( i, 1 );
   }

   int mini = 1, maxi = n;
 
   for( int i = 1; i <= n; ++i ) {
      if( i%2 == 1 ) {
         alive.add( position[mini], -1 );
         // printf("end: %d\n", position[mini]);
         printf( "%d\n", alive.sum( 1, position[mini] ) );
         ++mini;
      } else {
         alive.add( position[maxi], -1 );
         // printf("start: %d\n", position[maxi]);
         printf( "%d\n", alive.sum( position[maxi], n ) );
         --maxi;
      }
   }

   return 0;
}
