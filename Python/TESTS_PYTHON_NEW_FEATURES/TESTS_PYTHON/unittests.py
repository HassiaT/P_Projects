import unittest
import unittest.mock
from test_python import checking_str_duplicate
from test_python import find_index_first_non_repeating_char


''' Python version: 3.9.1 '''

class MyTestNewPythonFeaturesModule(unittest.TestCase):

    def test_checking_duplicates_empty_case(self):
        print("Starting test for checking if a string has duplicates - empty string")
        case_with_duplicates = ""
        result = checking_str_duplicate(case_with_duplicates)
        self.assertEqual(0, result, "The result should be 1 or TRUE")
      
    def test_checking_duplicates_duplicates(self):
        print("Starting test for checking if a string has duplicates - string with duplicates")
        case_with_duplicates = "abcbbgfgbjidqk"
        result = checking_str_duplicate(case_with_duplicates)
        self.assertEqual(0, result, "The result should be 1 or TRUE")
      
    def test_checking_duplicates_duplicates_no_duplicates(self):
        print("Starting test for checking if a string has duplicates - string with NO duplicates")
        case_with_duplicates = "abcfgik"
        result = checking_str_duplicate(case_with_duplicates)
        self.assertEqual(1, result, "The result should be 1 or TRUE")
      
    def test_find_first_index_duplicates_empty_string(self):
        self.str = ""
        index_found = find_index_first_non_repeating_char(self.str)
        self.assertEqual(-1, index_found, "The result should be -1")
    
    def test_find_first_index_duplicates_no_empty_string_all_repeating(self):
        self.str = "abcabcdeffedc"
        index_found = find_index_first_non_repeating_char(self.str)
        self.assertEqual(-1, index_found, "The result should be -1")
    
    def test_find_first_index_duplicates_no_empty_string_repeating_first(self):
        self.str = "abcdd"
        index_found = find_index_first_non_repeating_char(self.str)
        self.assertEqual(0, index_found, "The result should be 0")
        

    def test_find_first_index_duplicates_no_empty_string_repeating_last(self):
        self.str = "acbabcd"
        index_found = find_index_first_non_repeating_char(self.str)
        self.assertEqual(6, index_found, "The result should be 6")
        
    def test_find_first_index_duplicates_no_empty_string_repeating_in_middle(self):
        self.str = "ahfahpmfdmspjqj"
        index_found = find_index_first_non_repeating_char(self.str)
        self.assertEqual(8, index_found, "The result should be 0")
        

if __name__ == "__main__":
    unittest.main()
