#include <bits/stdc++.h>
#define disk_size 200
using namespace std;
int main()
{
    int total_head_movement = 0, initial_pos, n, direction;
    cout << "Enter number of disk requests : ";
    cin >> n;
    vector<int> request(n);
    cout << "Enter the disk requests : ";
    for (int i = 0; i < n; i++)
        cin >> request[i];
    cout << "Enter the initial position of the RW head: ";
    cin >> initial_pos;
    cout << "Enter the direction in which the Read Write head is moving:" << endl;
    cout << "Enter 0 if moving to higher cylinder else Enter 1: ";
    cin >> direction;
    vector<int> left, right;
    for (int i = 0; i < n; i++)
    {
        if (request[i] <= initial_pos)
            left.push_back(request[i]);
        else
            right.push_back(request[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    if (direction == 0)
    {
        if (!right.empty())
            right.push_back(disk_size - 1);
        for (int i = 0; i < right.size(); i++)
        {
            total_head_movement += abs(initial_pos - right[i]);
            initial_pos = right[i];
        }
        for (int i = left.size() - 1; i >= 0; i--)
        {
            total_head_movement += abs(initial_pos - left[i]);
            initial_pos = left[i];
        }
    }
    else
    {
        if (!left.empty())
            left.push_back(0);
        for (int i = left.size() - 1; i >= 0; i--)
        {
            total_head_movement += abs(initial_pos - left[i]);
            initial_pos = left[i];
        }
        for (int i = 0; i < right.size(); i++)
        {
            total_head_movement += abs(initial_pos - right[i]);
            initial_pos = right[i];
        }
    }
    cout << "\nTotal seek movement : " << total_head_movement << endl;
    return 0;
}