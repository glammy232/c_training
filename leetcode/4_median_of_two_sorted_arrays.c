#include <stdio.h>
#include <limits.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    if (nums1Size > nums2Size)
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);

    int m = nums1Size;
    int n = nums2Size;
    int total = m + n;
    int leftSize = (total + 1) / 2;

    int lo = 0, hi = m;

    while (lo <= hi) {
        int i = lo + (hi - lo) / 2;
        int j = leftSize - i;

        int nums1Left  = (i == 0) ? INT_MIN : nums1[i - 1];
        int nums1Right = (i == m) ? INT_MAX : nums1[i];
        int nums2Left  = (j == 0) ? INT_MIN : nums2[j - 1];
        int nums2Right = (j == n) ? INT_MAX : nums2[j];

        if (nums1Left > nums2Right) {
            hi = i - 1;
        } else if (nums2Left > nums1Right) {
            lo = i + 1;
        } else {
            int maxLeft = (nums1Left > nums2Left) ? nums1Left : nums2Left;

            if (total % 2 == 1) {
                return (double)maxLeft;
            }

            int minRight = (nums1Right < nums2Right) ? nums1Right : nums2Right;
            return (maxLeft + minRight) / 2.0;
        }
    }

    return 0.0;
}
