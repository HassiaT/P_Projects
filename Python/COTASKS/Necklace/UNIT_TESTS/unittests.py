import unittest
import unittest.mock
from SOLUTIONS.beads import collecting_beads_counting
from SOLUTIONS.beads import compute_collected_beads


class MyTestNecklaceTask(unittest.TestCase):
    
    def test_slicing(self):
        self.collar = "wwwwr"
        
    def test_collectingAndCount_case2(self):
        self.collar =  "rbw"
        result = collecting_beads_counting(reversed(self.collar))
        self.assertEqual(2, result, "We should collect 1 bead(s). Wrong answer")
        
    def test_collectingAndCount_case1(self):
        self.collar =  "rbw"
        self.length = len(self.collar)
        result = collecting_beads_counting(self.collar)
        self.assertEqual(1, result, "We should collect 1 bead(s). Wrong answer")

    def test_computingbreakpointofnecklace_case11(self):
        self.collar = "wwwbbrwrbrbrrbrbrwrwwrbwrwrrb"        
        self.length = len(self.collar)
        result = compute_collected_beads(self.collar,self.length)
        self.assertEqual(11, result, "We should collect 11 beads. Wrong answer")
    
    def test_computingbreakpointofnecklace_case8(self):
        self.collar = "brbrrrbbbrrrrrbrrbbrbbbbrrrrb"
        self.length = len(self.collar)
        result = compute_collected_beads(self.collar, self.length)
        self.assertEqual(8, result, "We should collect 8 beads. Wrong answer")
 
    def test_computingbreakpointofnecklace_case10(self):
        self.collar = "bbwbbrrrwbrbrrrrrb"
        self.length = len(self.collar)
        result = compute_collected_beads(self.collar,self.length)
        self.assertEqual(11, result, "We should collect 11 beads. Wrong answer")
  
    def test_computingbreakpointofnecklace_case3(self):
        self.collar = "wwr"
        self.length = len(self.collar)
        result = compute_collected_beads(self.collar,self.length)
        self.assertEqual(3, result, "We should collect 3 beads. Wrong answer")
 
  

if __name__ == "__main__":
    unittest.main()
