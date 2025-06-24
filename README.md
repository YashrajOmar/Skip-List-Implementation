⏫ Skip List Implementation
This project implements a Skip List, a probabilistic data structure that offers efficient O(log n) time complexity for search, insertion, and deletion operations. Skip Lists maintain multiple layers of linked lists, where each higher layer acts as an "express lane" for the layer below, enabling fast traversal.

Randomization is used to determine the height (level) of each node, resulting in performance similar to balanced trees but with simpler logic.

📌 Features
🔍 Search: Efficiently finds whether a given value exists in the skip list.

➕ Insert: Adds a new element while preserving the skip list’s ordered structure.

❌ Delete: Removes a specified element and maintains skip list balance.

🔽 Minimum: Retrieves the minimum element in the skip list.

📊 Traverse: Displays all elements level-by-level, showing skip list structure.

🧰 Technologies Used
Language: C++

Smart Pointers: std::shared_ptr for safe and automatic memory management

Randomization: Mersenne Twister (mt19937) for determining node heights

Standard Libraries: <memory>, <random>, <limits>, <vector>

⚙️ Setup Instructions
Ensure you have a C++17-compatible compiler (e.g., g++, clang++, MSVC).

Compile the files:

bash
Copy
Edit
g++ main.cpp skiplist.cpp -o skiplist -std=c++17
Run the executable:

bash
Copy
Edit
./skiplist
Ensure main.cpp, skiplist.cpp, and skiplist.h are in the same directory.

👥 Contributions
Contributions are welcome!
If you discover bugs or have suggestions for new features, feel free to fork the repo and open a pull request.

🖼️ Preview
A snapshot of the skip list output

![Screenshot 2025-06-25 012947](https://github.com/user-attachments/assets/6816f578-a9a5-4559-ba2f-3666d6b3226d)
