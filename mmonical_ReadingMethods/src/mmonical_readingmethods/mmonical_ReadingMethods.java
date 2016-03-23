/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mmonical_readingmethods;


//Name: Michael J Monical
//Class: 1400-003
//Program #: 3
//Due Date : February  3, 2016
//Colleagues: None
import java.util.Scanner;

public class mmonical_ReadingMethods {
    
    static Scanner get = new Scanner ( System.in );
    
    public static void main ( String args [] ) {

        double a, b, c, d, gff, ffc, grade;
    
        a = getWords();
        b = getSentences();
        c = getBigWords();
        d = getSyllables();
        
        //System.out.printf ( "The number of words you entered is: %.0f\n", a );
        //System.out.printf ( "The number of sentences you entered is: %.0f\n", b );
        //System.out.printf ( "The number of \"big words\" you entered is: %.0f\n", c );
        //System.out.printf ( "The number of syllables you entered is: %.0f\n\n", d );

        gff = GunningFog(a,b,c);
        ffc = FleschREScore(a,b,d);


        //The Flesch Grade Level

        grade = ffc;
        grade = FleschGL(ffc);
        displayResults(gff, ffc, grade);

//I did place an extra new line (\n) at the bottom for easier readability!!
    }
    
    public static double getWords(){
        System.out.print( "Please enter the number of words in the sample: " );
        return get.nextDouble( );
    }
    
    public static double getSentences(){
        System.out.print( "Please enter the number of sentences in the sample: " );
        return get.nextDouble( );
    }
    
    public static double getBigWords(){
        System.out.print( "Please enter the number of big words in the sample: " );
        return get.nextDouble( );
    }
    
    public static double getSyllables(){
        System.out.print( "Please enter the number of syllables in the sample: ");
        return get.nextDouble( );
    }
    
    public static double GunningFog(double a,double b,double c){
        //The Gunning Fog Index
        double gfa = a / b; //gfa stands for gunning fox a
        //System.out.printf ( "The average sentence length is %.2f\n", gfa);
        double gfb = (c / a) * 100.0; // gfb stand for gunning fox b
        //System.out.printf ( "The percentage of \"big words\" is %.2f\n", gfb);
        return (gfa + gfb) * 0.40; //gff stands for gunning fox final
    }
    
    public static double FleschREScore(double a, double b, double c){
        //The Flesch Formula

        double ffa = (a / b) * 1.015; //Flesch Formula variable a step 3
        double ffb = (c / a) * 84.6; //Flesch formula b step 4
        return 206.835 - (ffa + ffb);
    }
            
    public static double FleschGL(double a){
        return a;
    }
            
    public static void displayResults(double a,double b,double c){
        System.out.printf ( "\nThe Gunning Fog Index of this sample is: %.2f\n", a);
        System.out.printf ( "The Reading Ease Score is: %.2f\n", c);
        System.out.print( "The Flesch Grade Level is: ");
        if(c > 100)
            System.out.println ( "Not defined\n" );
        else if ( c >= 90)
            System.out.println ( "4th to 5th grade\n" );
        else if ( c >= 80 )
            System.out.println ( "5th to 6th grade\n" );
        else if (c >= 70 ) 
            System.out.println ( "7th grade\n" );
        else if (c >= 60 )
            System.out.println ( "8th to 9th grade\n" );
        else if (c >= 50 )
            System.out.println ( "High School\n" );
        else if (c >= 30)
            System.out.println ( "College\n" );
        else if (c >= 0)
            System.out.println ( "Post Graduate\n" );
        else
            System.out.println ( "Not defined\n");
    }
}
