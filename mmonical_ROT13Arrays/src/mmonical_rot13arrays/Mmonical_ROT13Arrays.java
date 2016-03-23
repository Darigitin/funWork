/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mmonical_rot13arrays;
import java.util.Scanner;
/**
 *
 * @author mike
 */
public class Mmonical_ROT13Arrays {

    /**
     * @param args the command line arguments
     */
    public static Scanner get = new Scanner (System.in);
    public static void main(String[] args) {
        // TODO code application logic here
    //Name: Michael J Monical
//Class: 1400-003
//Program #: 6 
//Due Date: February 24th, 2016
//Colleagues : None

       


        char ch;
        int a;
        boolean boolflag;
        int counter = 0;
        System.out.print ("Enter a sentence to ROT13: ");
        String sentence = get.nextLine();
        sentence = sentence.toUpperCase();
        
        for (a = 0; a < sentence.length(); a++){
            ch = sentence.charAt(a);
            int hexChar = (int) ch;
            if (hexChar == 0x20)
                System.out.print(" ");
            if (hexChar < 0x41){
                continue;
            }
            else if (hexChar > 0x5A){
                continue;
            }
            hexChar = (hexChar + 0x0D) % 0x5B;
            if (hexChar < 0x41)
                hexChar = hexChar + 0x41;
            System.out.print((char)hexChar);
        }
        System.out.println("");
        a = 0;
        while ( a != sentence.length() )
        {
            ch = sentence.charAt(a++);
            boolflag = false;
            
            switch (ch)
            {
                case 'A':
                    System.out.printf("N");
                    break;

                case 'B':
                    System.out.printf("O");
                    break;
                case 'C':
                    System.out.printf("P");
                    break;
                case 'D':
                    System.out.printf("Q");
                    break;
                case 'E':
                    System.out.printf("R");
                    break;
                case 'F':
                    System.out.printf("S");
                    break;
                case 'G':
                    System.out.printf("T");
                    break;
                case 'H':
                    System.out.printf("U");
                    break;
                case 'I':
                    System.out.printf("V");
                    break;
                case 'J':
                    System.out.printf("W");
                    break;
                case 'K':
                    System.out.printf("X");
                    break;
                case 'L':
                    System.out.printf("Y");
                    break;
                case 'M':
                    System.out.printf("Z");
                    break;
                case 'N':
                    System.out.printf("A");
                    break;
                case 'O':
                    System.out.printf("B");
                    break;
                case 'P':
                    System.out.printf("C");
                    break;
                case 'Q':
                    System.out.printf("D");
                    break;
                case 'R':
                    System.out.printf("E");
                    break;
                case 'S':
                    System.out.printf("F");
                    break;
                case 'T':
                    System.out.printf("G");
                    break;
                case 'U':
                    System.out.printf("H");
                    break;
                case 'V':
                    System.out.printf("I");
                    break;
                case 'W':
                    System.out.printf("J");
                    break;
                case 'X':
                    System.out.printf("K");
                    break;
                case 'Y':
                    System.out.printf("L");
                    break;
                case 'Z':
                    System.out.printf("M");
                    break;
                default:
                    System.out.printf("");
                    boolflag = true;
                    break;
            }
        if (!boolflag)
        {
            counter++;
            if (counter == 5)
            {
                System.out.printf(" ");
                counter = 0;
            }
        }
            
        }
        System.out.println("\n");


    }
}
