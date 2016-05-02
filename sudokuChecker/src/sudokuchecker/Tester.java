package sudokuChecker;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.Scanner;
public class Tester {
    public static void main ( String args[] ) {
        Scanner get = new Scanner ( System.in );
        System.out.print( "Enter filename of potential Sudoku: " );
        String filename = get.next();
        sudokuChecker thing = new sudokuChecker(filename);
        thing.display();
        boolean a = thing.checkRows();
        boolean b = thing.checkColumns();
        boolean c = thing.checkRegions();
        
        if ( a == true && b == true && c == true ) {
        System.out.println( "\nSudoku: YES" );
        }
        else {
        System.out.println( "\nSudoku: NO" );
        }
    }
}