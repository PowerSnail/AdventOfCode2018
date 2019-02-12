/**
--- Day 4: Repose Record ---

You've sneaked into another supply closet - this time, it's across from the
prototype suit manufacturing lab. You need to sneak inside and fix the issues
with the suit, but there's a guard stationed outside the lab, so this is as
close as you can safely get.

As you search the closet for anything that might help, you discover that you're
not the first person to want to sneak in. Covering the walls, someone has spent
an hour starting every midnight for the past few months secretly observing this
guard post! They've been writing down the ID of the one guard on duty that night
- the Elves seem to have decided that one guard was enough for the overnight
shift - as well as when they fall asleep or wake up while at their post (your
puzzle input).

For example, consider the following records, which have already been organized
into chronological order:

[1518-11-01 00:00] Guard #10 begins shift
[1518-11-01 00:05] falls asleep
[1518-11-01 00:25] wakes up
[1518-11-01 00:30] falls asleep
[1518-11-01 00:55] wakes up
[1518-11-01 23:58] Guard #99 begins shift
[1518-11-02 00:40] falls asleep
[1518-11-02 00:50] wakes up
[1518-11-03 00:05] Guard #10 begins shift
[1518-11-03 00:24] falls asleep
[1518-11-03 00:29] wakes up
[1518-11-04 00:02] Guard #99 begins shift
[1518-11-04 00:36] falls asleep
[1518-11-04 00:46] wakes up
[1518-11-05 00:03] Guard #99 begins shift
[1518-11-05 00:45] falls asleep
[1518-11-05 00:55] wakes up

Timestamps are written using year-month-day hour:minute format. The guard
falling asleep or waking up is always the one whose shift most recently started.
Because all asleep/awake times are during the midnight hour (00:00 - 00:59),
only the minute portion (00 - 59) is relevant for those events.

Visually, these records show that the guards are asleep at these times:

Date   ID   Minute
            000000000011111111112222222222333333333344444444445555555555
            012345678901234567890123456789012345678901234567890123456789
11-01  #10  .....####################.....#########################.....
11-02  #99  ........................................##########..........
11-03  #10  ........................#####...............................
11-04  #99  ....................................##########..............
11-05  #99  .............................................##########.....

The columns are Date, which shows the month-day portion of the relevant day; ID,
which shows the guard on duty that day; and Minute, which shows the minutes
during which the guard was asleep within the midnight hour. (The Minute column's
header shows the minute's ten's digit in the first row and the one's digit in
the second row.) Awake is shown as ., and asleep is shown as #.

Note that guards count as asleep on the minute they fall asleep, and they count
as awake on the minute they wake up. For example, because Guard #10 wakes up at
00:25 on 1518-11-01, minute 25 is marked as awake.

If you can figure out the guard most likely to be asleep at a specific time, you
might be able to trick that guard into working tonight so you can have the best
chance of sneaking in. You have two strategies for choosing the best
guard/minute combination.

Strategy 1: Find the guard that has the most minutes asleep. What minute does
that guard spend asleep the most?

In the example above, Guard #10 spent the most minutes asleep, a total of 50
minutes (20+25+5), while Guard #99 only slept for a total of 30 minutes
(10+10+10). Guard #10 was asleep most during minute 24 (on two days, whereas any
other minute the guard was asleep was only seen on one day).

While this example listed the entries in chronological order, your entries are
in the order you found them. You'll need to organize them before they can be
analyzed.

What is the ID of the guard you chose multiplied by the minute you chose? (In
the above example, the answer would be 10 * 24 = 240.)

Strategy 2: Of all guards, which guard is most frequently asleep on the same minute?

In the example above, Guard #99 spent minute 45 asleep more than any other guard or minute - three times in total. (In all other cases, any guard spent any minute asleep at most twice.)

What is the ID of the guard you chose multiplied by the minute you chose? (In the above example, the answer would be 99 * 45 = 4455.)
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <numeric>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;


struct Log {
  int minute;
  char type;
  int guard_id;
};

Log ParseLine(string& line) {
  Log l;
  int hour = std::stoi(line.substr(12, 2));
  l.minute = (hour == 0) ? std::stoi(line.substr(15, 2)) : 0;
  l.type = line[19];
  l.guard_id = (l.type == 'G')
                   ? std::stoi(line.substr(26, line.find(' ', 26) - 26))
                   : -1;
  return l;
}

void IncrRange(vector<int>& array, int from, int to) {
  for (int i = from; i < to; ++i) {
    array[i] += 1;
  }
}

int main() {
  string line;
  vector<string> logs;
  while (std::getline(cin, line)) {
    logs.push_back(line);
  }
  std::sort(logs.begin(), logs.end());

  unordered_map<int, vector<int>> sleep_map;

  bool wake = true;
  int current_guard = -1;
  int prev_minute = 0;

  for (auto& s : logs) {
    Log l = ParseLine(s);
    switch (l.type) {
      case 'G':
        if (!wake) {
          IncrRange(sleep_map[current_guard], prev_minute, l.minute);
        }
        current_guard = l.guard_id;
        wake = true;
        if (sleep_map.find(current_guard) == sleep_map.end()) {
          sleep_map[current_guard] = vector(60, 0);
        }
        break;
      case 'f':
        wake = false;
        break;
      case 'w':
        IncrRange(sleep_map[current_guard], prev_minute, l.minute);
        wake = true;
        break;
      default:
        std::cerr << "Parsing Error" << endl;
        break;
    }
    prev_minute = l.minute;
  }

  int max_sum = -1, max_prod = -1;
  for (const auto & entry : sleep_map) {
    const auto& arr = entry.second;
    int sum = std::accumulate(arr.begin(), arr.end(), 0);
    if (sum > max_sum) {
      max_sum = sum;
      max_prod = entry.first * (std::max_element(arr.begin(), arr.end()) - arr.begin());
    }
  }

  cout << "Product of ID and minute is " << max_prod << endl;

  int max_freq = -1, max_prod2 = -1;
  for (const auto& entry: sleep_map) {
    const auto& arr = entry.second;
    auto max_element = std::max_element(arr.begin(), arr.end());
    if (*max_element > max_freq) {
      max_freq = *max_element;
      max_prod2 = entry.first * (max_element - arr.begin());
    }
  }

  cout << "Product of ID and minute is " << max_prod2 << endl;

}
