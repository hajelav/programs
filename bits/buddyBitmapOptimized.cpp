 private int[][] bits;

  private int n;

  private int numNodesLastLevel;

   

  public Solution (int n) {

    this.n = n;

    this.numNodesLastLevel = (int) Math.pow(2, n - 1);

    bits = new int[n][numNodesLastLevel];

     

     

  }

   

  public void clearBits(int offset, int len) {

    if (offset < 0 || offset + len > numNodesLastLevel) {

      throw new IndexOutOfBoundsException();

    }

    clearBitsHelper(n - 1, offset, offset + len - 1);

  }

   

  private void clearBitsHelper(int level, int start, int end) {

    if (level < 0 || start > end) {

      return;

    }

     

    boolean containsOne = setToZero(level, start ,end);

    if (containsOne) {

      clearBitsHelper(level - 1, start / 2, end / 2);

    }

  }

   

  public void setBits(int offset, int len) {

    if (offset < 0 || offset + len > numNodesLastLevel) {

      throw new IndexOutOfBoundsException();

    }

    setBitsHelper(n - 1, offset, offset + len - 1);

  }

   

  private void setBitsHelper(int level, int start, int end) {

    if (level < 0 || start > end) {

      return;

    }

     

    setToOne(level, start, end);

     

    // if start index is odd

    if ((start & 1) == 1) {

      start--;

    }

     

    // if end index is even

    if ((end & 1) == 0) {

      end++;

    }

     

    // determine the start position of the next level

    int nextStart = Integer.MAX_VALUE;

    for (int i = start; i < end; i += 2) {

      if (bits[level][i] == 1 && bits[level][i + 1] == 1) {

        nextStart = i / 2;

        break;

      }

    }

     

    // determien the end position of the next level

    int nextEnd = Integer.MIN_VALUE;

    for (int i = end; i > start; i -= 2) {

      if (bits[level][i] == 1 && bits[level][i - 1] == 1) {

        nextEnd = i / 2;

        break;

      }

    }

     

    setBitsHelper(level - 1, nextStart, nextEnd);

  }

   

  private void setToOne(int level, int start, int end) {

    for (int i = start; i <= end; i++) {

      bits[level][i] = 1;

    }

  }

   

  private boolean setToZero(int level, int start, int end) {

    boolean containsOne = false;

    for (int i = start; i <= end; i++) {

      if (bits[level][i] == 1) {

        containsOne = true;

      }

       

      bits[level][i] = 0;

    }

     

    return containsOne;

  }

   

   

   

  private void printTree() {

    int nodes = 1;

    for (int[] level : bits) {

      for (int i = 0; i < nodes; i++) {

        System.out.print(level[i] + ", ");

      }

       

      System.out.println("");

      nodes *= 2;

    }

    System.out.println("");

  }

   

  public static void main(String[] args) {

    Solution sol = new Solution(4);

     

    sol.setBits(1, 5);

    sol.printTree();

     

    sol.clearBits(2, 6);

    sol.printTree();

  }
