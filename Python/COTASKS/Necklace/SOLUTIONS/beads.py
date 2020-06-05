"""
TASK : beads
"""


def collecting_beads_counting(necklace):
    BLUE = False
    RED = False
    count = 0    
    for bead in necklace:
        if bead == 'r':
            if BLUE:
                break
            else:
                RED = True
        if bead == 'b':
            if RED:
                break
            else:
                BLUE = True
        count+= 1    
    return count


def compute_collected_beads(necklace, length_necklace):
    COLLECTED_BEADS = 0
    joined_necklace = necklace + necklace
    for breakpoint in range(0,length_necklace,1):
        LEFT = joined_necklace[0: breakpoint+1]
        LEFT_COLLECTED = collecting_beads_counting(reversed(LEFT))
        if breakpoint - LEFT_COLLECTED > 0:
           RIGHT = necklace[(breakpoint+1):] + necklace[0:breakpoint - LEFT_COLLECTED]
        else:
           RIGHT = necklace[(breakpoint+1):]
        RIGHT_COLLECTED = collecting_beads_counting(RIGHT)
        if LEFT_COLLECTED + RIGHT_COLLECTED > COLLECTED_BEADS:
            COLLECTED_BEADS = (LEFT_COLLECTED + RIGHT_COLLECTED)
    return COLLECTED_BEADS


    
def solving_beads_task():
    FILE_INPUT = "beads.in"
    fin = open (FILE_INPUT, 'r')
    fout = open ("beads.out", 'w')
    CONTENT = fin.read().split('\n')
    NECKLACE_LENGTH = int(CONTENT[0])
    READ_NECKLACE = str(CONTENT[1])
    collected_beads = compute_collected_beads(READ_NECKLACE,NECKLACE_LENGTH)
    fout.write (str(collected_beads) + '\n')
    fout.close()
    fin.close()
  
    
def main():
    solving_beads_task()

if __name__ == "__main__":
    main()