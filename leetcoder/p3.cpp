class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int char_index[256] = {0};
        int result = 0, anchor = 0;
        for (int i=0; i<s.length(); i++) {
            if (char_index[s[i]] != 0 && anchor < char_index[s[i]]) {
                anchor = char_index[s[i]];
            } else {
                result = max(i-anchor+1, result);
            }
            char_index[s[i]] = i+1;
        }
        return result;
    }
};
