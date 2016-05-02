/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudokuChecker;

import java.io.File;
import java.util.Scanner;

/**
 *
 * @author mike
 */
public class sudokuChecker {

    private int[][] grid = new int[9][9];
    
    
    /**
     * SudokuChecker()
     * 
     * This is the constructor method for the class. It will not have a return
     * type, and the name of the method needs to match the name of the class
     * exactly.
     * 
     * This method takes as an argument a String that is the name of a file. It
     * should open up the file and read in the file contents into the 2-d int 
     * array "grid" that is a private instance variable of the class.
     * 
     * @param inputFile a String containing the input file name
     */
    public sudokuChecker(String inputFile)
    {
        // TODO code application logic here
        System.out.printf("Loading %s ...\n", inputFile);
        try{
            File file = new File(inputFile);
            Scanner input = new Scanner (file);
            for (int i = 0; i < grid.length; i++){
                for (int j = 0; j < grid.length; j++){
                    grid[i][j] = input.nextInt();
                }
            }
            
        }catch(Exception ex){
            System.out.println("An error has occured");
            System.out.println(ex.toString());
        }
    }
    
    /**
     * display()
     * 
     * This method displays the square to the screen. There should not be any
     * labeling of the rows or columns, but separating the output into regions 
     * is required for easier visual identification of each region of the Sudoku
     * grid. See the sample runs for examples.
     */
    public void display()
    {
        for (int i = 0; i < grid.length; i++){
            for (int j = 0; j < grid.length; j++){
                System.out.printf(" %d ", grid[i][j]);
                
                if ( ((j + 1) % 3) == 0 && j != 0 && j != grid.length - 1){
                    System.out.print("|");
                }
            }
            System.out.println("");
            if ( ((i + 1) % 3) == 0 && i != 0 && i != grid.length - 1){
                System.out.println("-------------------------------");
            }
        }
    }
    
    /**
     * checkRows()
     * 
     * This method checks each row to see if it is a valid row, with each
     * value between 1 and 9 inclusive being used only once.
     * 
     * The method should label each of the 9 rows and then identify if the
     * column is GOOD or BAD by outputting the text GOOD or BAD. There is no
     * need to identify which values are bad (either duplicated or missing).
     * 
     * The method should return true if all of the rows are valid and false
     * otherwise.
     * 
     * 
     * @return boolean true or false if all the rows are valid. 
     */
    public boolean checkRows()
    {
        boolean boo = true;
        boolean boo2 = true;
        for (int i = 0; i < grid.length; i++){
            for (int j = 0; j < grid.length; j++){
                for (int k = 0; k < grid.length; k++){
                    if (j != k){
                        if (grid[i][j] == grid[i][k]){
                            boo = false;
                            boo2 = false;
                        }
                    }
                }
            }
            if (boo2){
                System.out.printf("ROW %d: GOOD\n", i+1);
            }
            else{
                System.out.printf("ROW %d: BAD\n", i+1);
                boo2 = true;
            }
        }
        
        return boo;
    }
        /**
     * checkColumns()
     * 
     * This method checks each column to see if it is a valid column, with each
     * value between 1 and 9 inclusive being used only once.
     * 
     * The method should label each of the 9 columns and then identify if the
     * column is GOOD or BAD by outputting the text GOOD or BAD. There is no
     * need to identify which values are bad (either duplicated or missing).
     * 
     * The method should return true if all of the columns are valid and false
     * otherwise.
     * 
     * 
     * @return boolean true or false if all the columns are valid. 
     */
    public boolean checkColumns()
    {
        boolean boo = true;
        boolean boo2 = true;
        for (int i = 0; i < grid.length; i++){
            for (int j = 0; j < grid.length; j++){
                for (int k = 0; k < grid.length; k++){
                    if (j != k){
                        if (grid[j][i] == grid[k][i]){
                            boo = false;
                            boo2 = false;
                        }
                    }
                }
            }
            if (boo2){
                System.out.printf("COLUMN %d: GOOD\n", i+1);
            }
            else{
                System.out.printf("COLUMN %d: BAD\n", i+1);
                boo2 = true;
            }
        }
        
        return boo;
    }
    
    /**
     * checkRegions()
     * 
     * This method checks each region to see if it is a valid region, with each
     * value between 1 and 9 inclusive being used only once.
     * 
     * The method should label each of the 9 regions and then identify if the
     * column is GOOD or BAD by outputting the text GOOD or BAD. There is no
     * need to identify which values are bad (either duplicated or missing).
     * 
     * The method should return true if all of the regions are valid and false
     * otherwise.
     * 
     * 
     * @return boolean true or false if all the regions are valid. 
     */
    public boolean checkRegions()
    {
        //i is for region row
        //j is for region column
        //k is for region inner row
        //l is for region inner column
       boolean boo = true;
       boolean boo2 = true;
       for (int i = 0; i < grid.length / 3; i++){
           for (int j = 0; j < grid.length / 3; j++){
               for (int k = i*3; k < (i+1) * 3 - 1; k++){
                   for (int l = j*3; l < (j+1) * 3 - 1; l++){
                     //  System.out.printf("grid[%d][%d]\n", k,l);
                       for (int m = k; m <= (i+1) * 3 - 1; m++){
                           for (int n = l; n <= (j+1) * 3 - 1; n++){
                                if (!(k == m && l == n)){
                                   // System.out.printf("(grid[%d][%d] = %d) =? (grid[%d][%d] = %d)\n", k, l, grid[k][l], m, n, grid[m][n]);
                                    if (grid[k][l] == grid[m][n]){
                                        boo = false;
                                        boo2 = false;
                                    }
                                }
                            }
                        }
                    }
                }
                if (boo2){
                    System.out.printf("REGION %d: GOOD\n", 3*i + j + 1);
                }
                else{
                    System.out.printf("REGION %d: BAD\n", 3*i + j + 1);
                    boo2 = true;
                }
            }
       } 
       
        return boo;
    }

}



/*

        [region 1] [region 2] [region 3]
        [region 4] [region 5] [region 6]
        [region 7] [region 8] [region 9]

        where each region is a 2D array.
                        3*i + j + 1
        [0][0] = 1      3*0 + 0 + 1 = 1
        [0][1] = 2      3*0 + 1 + 1 = 2
        [0][2] = 3      3*0 + 2 + 1 = 3
        [1][0] = 4      3*1 + 0 + 1 = 4
        [1][1] = 5      3*1 + 1 + 1 = 5
        [1][2] = 6      3*1 + 2 + 1 = 6
        [2][0] = 7      3*2 + 0 + 1 = 7
        [2][1] = 8      3*2 + 1 + 1 = 8
        [2][2] = 9      3*2 + 2 + 1 = 9
*/