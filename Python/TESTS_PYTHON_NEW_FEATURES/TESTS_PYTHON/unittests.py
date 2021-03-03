import unittest
import unittest.mock
import test_python


''' Python version: 3.9.1 '''

class MyTestNewPythonFeaturesModule(unittest.TestCase):
    
    def test_checking_duplicates_empty_case(self):
        print("Starting test for checking if a string has duplicates - empty string")
        case_with_duplicates = ""
        result = test_python.checking_str_duplicate(case_with_duplicates)
        self.assertEqual(0, result, "The result should be 1 or TRUE")
      
    def test_checking_duplicates_duplicates(self):
        print("Starting test for checking if a string has duplicates - string with duplicates")
        case_with_duplicates = "abcbbgfgbjidqk"
        result = test_python.checking_str_duplicate(case_with_duplicates)
        self.assertEqual(0, result, "The result should be 1 or TRUE")
      
    def test_checking_duplicates_duplicates_no_duplicates(self):
        print("Starting test for checking if a string has duplicates - string with NO duplicates")
        case_with_duplicates = "abcfgik"
        result = test_python.checking_str_duplicate(case_with_duplicates)
        self.assertEqual(1, result, "The result should be 1 or TRUE")
      
        
if __name__ == "__main__":
    unittest.main()
