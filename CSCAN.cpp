#include <bits/stdc++.h>
#include <algorithm>
#define total_cylinders 200
using namespace std;
int main()
{
    int total_head_movement = 0, initial_pos, n, direction;
    cout << "\nEnter the number of disk requests: ";
    cin >> n;
    vector<int> request(n);
    cout << "\nEnter the cylinder numbers in the request queue:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> request[i];
    }
    cout << "\nEnter the initial position of the RW head: ";
    cin >> initial_pos;
    cout << "\nEnter the direction in which the Read Write head is moving:";
    cout << "\nEnter 0 if moving to higher cylinder else Enter 1: ";
    cin >> direction;
    vector<int> left, right;
    for (int i = 0; i < n; i++)
    {
        if (request[i] < initial_pos)
        {
            left.push_back(request[i]);
        }
        else
        {
            right.push_back(request[i]);
        }
    }
    right.push_back(total_cylinders - 1);
    left.push_back(0);
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    if (direction == 0)
    {
        for (int i = 0; i < right.size(); i++)
        {
            total_head_movement += abs(initial_pos - right[i]);
            initial_pos = right[i];
        }
        total_head_movement += abs(initial_pos - 0);
        initial_pos = 0;
        for (int i = 0; i < left.size(); i++)
        {
            total_head_movement += abs(initial_pos - left[i]);
            initial_pos = left[i];
        }
    }
    else
    {
        for (int i = left.size() - 1; i >= 0; i--)
        {
            total_head_movement += abs(initial_pos - left[i]);
            initial_pos = left[i];
        }
        total_head_movement += abs(initial_pos - (total_cylinders - 1));
        initial_pos = total_cylinders - 1;
        for (int i = right.size() - 1; i >= 0; i--)
        {
            total_head_movement += abs(initial_pos - right[i]);
            initial_pos = right[i];
        }
    }
    cout << "\n\nTotal head movement: " << total_head_movement << endl;
    return 0;
}