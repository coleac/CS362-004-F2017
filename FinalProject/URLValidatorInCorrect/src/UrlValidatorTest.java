/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import junit.framework.TestCase;
import java.io.*;

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
      
      
   }
   
   @SuppressWarnings("deprecation")
   public void testManualTest()
   {
	   int urlCounter = 0;
	   boolean result;
	   String strLine;
 
	   System.out.println("--------------------START MANUAL TESTING--------------------");
	   
	   
	   //Open the input file
	   InputStream in = UrlValidatorTest.class.getResourceAsStream("UrlsToVerify.txt");   
		  
	   try
	   {
		   
		   //Get the object of DataInputStream
		   BufferedReader br = new BufferedReader(new InputStreamReader(in));		   
		   
		   //Create UrlValidator object
		   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		   
		   //Execute pre-existing test
		   System.out.println(urlVal.isValid("http://www.amazon.com"));
		   System.out.println();
		   
		   //Read file line by line
		   while ((strLine = br.readLine()) != null)   
		   {
			   
			   //run UrlValidator program by calling isValid() method with URLs in input file
			   result = urlVal.isValid(strLine);
			       	  
			   urlCounter++;
			   //First 26 URLs are valid
			   if (urlCounter <= 26) 
			   {
				   if (result == false) 
				   {
					   //Write to console failed tests
					   System.out.println("Expected result = true.  Actual result = " + result + ".");
					   System.out.println("Test failed: " + strLine);
					   System.out.println();
				   }
			   }
			   //Last 15 URLs are invalid
			   else 
			   {
				   if (result == true) 
				   {
					   //Write to console failed tests
					   System.out.println("Expected result = false.  Actual result = " + result + ".");
					   System.out.println("Test failed: " + strLine);
					   System.out.println();   
				   }	
			   }    
		   }
		   //Close the input stream
		   in.close();		   
	   }
	   
	   catch (Exception e)
	   {	//Catch exception if any
		   System.err.println("Error: " + e.getMessage());
	   }	      
	    
	    System.out.println("--------------------MANUAL TESTING FINISHED--------------------");
	    
	    System.out.println("");
	    System.out.println("--------------------START PARTITION TESTING--------------------");
   }
	   
   
   public void testYourFirstPartition()
   {
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
       System.out.println("Testing Valid: SCHEME + www.google.com");
       
       String[] testPart = getValidSchemes();
       for (int i = 0; i < testPart.length; i++)
       {
           String testURL = testPart[i] + "www.google.com";
           boolean testVal = urlVal.isValid(testURL);
           //assertEquals(testURL, true, testVal);
           if (testVal) {
               System.out.println("Passed: " + testURL);
           }
           else {
               System.out.println("Failed: " + testURL);
           }
       }
       
       System.out.println("Testing Invalid: SCHEME + www.google.com");
       testPart = getInvalidSchemes();
       for (int i = 0; i < testPart.length; i++)
       {
           String testURL = testPart[i] + "www.google.com";
           boolean testVal = urlVal.isValid(testURL);
           //assertEquals(testURL, false, testVal);
           if (testVal) {
               System.out.println("Passed: " + testURL);
           }
           else {
               System.out.println("Failed: " + testURL);
           }
       }    
   }
   
   
   public void testYourSecondPartition()
   {
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
       System.out.println("Testing Valid: http:// + AUTHORITY");
       String[] testPart = getValidAuthority();
       for (int i = 0; i < testPart.length; i++)
       {
           String testURL = "http://" + testPart[i];
           boolean testVal = urlVal.isValid(testURL);
           //assertEquals(testURL, true, testVal);
           if (testVal) {
               System.out.println("Passed: " + testURL);
           }
           else {
               System.out.println("Failed: " + testURL);
           }
       }
       
       System.out.println("Testing Invalid: http:// + AUTHORITY");
       testPart = getInvalidAuthority();
       for (int i = 0; i < testPart.length; i++)
       {
           String testURL = "http://" + testPart[i];
           boolean testVal = urlVal.isValid(testURL);
           //assertEquals(testURL, false, testVal);
           if (testVal) {
               System.out.println("Passed: " + testURL);
           }
           else {
               System.out.println("Failed: " + testURL);
           }
       }    
   }
   
   public void testYourThirdPartition()
   {
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
       System.out.println("Testing Valid: http:// + www.google.com + PORT");
       String[] testPart = getValidPort();
       for (int i = 0; i < testPart.length; i++)
       {
           String testURL = "http://www.google.com" + testPart[i];
           boolean testVal = urlVal.isValid(testURL);
           //assertEquals(testURL, true, testVal);
           if (testVal) {
               System.out.println("Passed: " + testURL);
           }
           else {
               System.out.println("Failed: " + testURL);
           }
       }
       
       System.out.println("Testing Invalid: http:// + www.google.com + PORT");
       testPart = getInvalidPort();
       for (int i = 0; i < testPart.length; i++)
       {
           String testURL = "http://www.google.com" + testPart[i];
           boolean testVal = urlVal.isValid(testURL);
           //assertEquals(testURL, false, testVal);
           if (testVal) {
               System.out.println("Passed: " + testURL);
           }
           else {
               System.out.println("Failed: " + testURL);
           }
       }
       
   }
   
   public void testYourFourthPartition()
   {
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
       System.out.println("Testing Valid: http:// + www.google.com + PATH");
       String[] testPart = getValidPath();
       for (int i = 0; i < testPart.length; i++)
       {
           String testURL = "http://www.google.com" + testPart[i];
           boolean testVal = urlVal.isValid(testURL);
           //assertEquals(testURL, true, testVal);
           if (testVal) {
               System.out.println("Passed: " + testURL);
           }
           else {
               System.out.println("Failed: " + testURL);
           }
       }
       
       System.out.println("Testing Invalid: http:// + www.google.com + PATH");
       testPart = getInvalidPath();
       for (int i = 0; i < testPart.length; i++)
       {
           String testURL = "http://www.google.com" + testPart[i];
           boolean testVal = urlVal.isValid(testURL);
           //assertEquals(testURL, false, testVal);
           if (testVal) {
               System.out.println("Passed: " + testURL);
           }
           else {
               System.out.println("Failed: " + testURL);
           }
       }
   }
   
   public void testYourFifthPartition()
   {
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
       System.out.println("Testing Valid: http:// + www.google.com + QUERY");
       String[] testPart = getValidQuery();
       for (int i = 0; i < testPart.length; i++)
       {
           String testURL = "http://www.google.com" + testPart[i];
           boolean testVal = urlVal.isValid(testURL);
           //assertEquals(testURL, true, testVal);
           if (testVal) {
               System.out.println("Passed: " + testURL);
           }
           else {
               System.out.println("Failed: " + testURL);
           }
       }
       
       System.out.println("Testing Invalid: http:// + www.google.com + QUERY");
       testPart = getInvalidQuery();
       for (int i = 0; i < testPart.length; i++)
       {
           String testURL = "http://www.google.com" + testPart[i];
           boolean testVal = urlVal.isValid(testURL);
           //assertEquals(testURL, true, testVal);
           if (testVal) {
               System.out.println("Passed: " + testURL);
           }
           else {
               System.out.println("Failed: " + testURL);
           }
       }
   }
   public String[] getValidSchemes() {
       String[] schemes = {"http://", "hhttp://"};
       return schemes;
   }
   
   public String[] getInvalidSchemes() {
       String[] schemes = {"http", "http:///", "://", ""};
       return schemes;
   }
   
   public String[] getValidAuthority() {
       String[] authority = {"www.google.com", "google.com", "1.1.1.1", "0.0.0.0", "w.google.com" };
       return authority;
   }
   
   public String[] getInvalidAuthority() {
       String[] authority = {"www.google", "www.google.c", "google",
               "www..com", "-1.-1.-1.-1", "256.256.256.256" };
       return authority;
   }
   
   public String[] getValidPort() {
       String[] port = {":0", ":1", ":65535"};
       return port;
   }
   
   public String[] getInvalidPort() {
       String[] port = {":-1", ":65536"};
       return port;
   }
   
   public String[] getValidPath() {
       String[] path = {"/", "/abc"};
       return path;
   }
   
   public String[] getInvalidPath() {
       String[] path = {"//", "abc"};
       return path;
   }
   
   public String[] getValidQuery() {
       String[] query = {"?action=view", "?action=view&mode=up"};
       return query;
   }
   
   public String[] getInvalidQuery() {
       String[] query = {"action=view", "?" };
       return query;
   }
   
   // uses the runPartTest method to test validation of the various parts of a URL
   public void testProgrammingBasedUnitTest()
   {
	   System.out.println("");
	   System.out.println("--------------------PARTITION TESTING FINISHED--------------------");
	   System.out.println("");
	   System.out.println("--------------------START PROGRAMMING BASED TESTING--------------------");
	   System.out.println("");
	   
	   runPartTest(testUrlScheme, "URLScheme", "www.oregonstate.edu", true);
	   runPartTest(testUrlAuthority, "URLAuthority", "http://", false);
	   runPartTest(testUrlPort, "URLPort", "http://www.oregonstate.edu", false);
	   runPartTest(testPath, "testPath", "http://www.oregonstate.edu:80", false);
	   runPartTest(testUrlQuery, "testUrlQuery", "http://www.oregonstate.edu:80/test1", false);
	   
	   System.out.println("--------------------PROGRAMMING BASED TESTING FINISHED--------------------");
	   
   }
   
   // constructs and tests URLs using the constant partialURL and items from the URLPiece array
   private void runPartTest (ResultPair[] URLPiece, String testName, String partialURL, boolean insertBeforePartial) {
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("-----------------------------------------------------------------");
	   System.out.println("TESTING " + testName + " validation. Failed tests will be printed...");
	   System.out.println("-----------------------------------------------------------------");
	   int testsFailed = 0;
	   String Url;
	   
	   for(int i = 0; i < URLPiece.length; i++) {
		   
		   if(insertBeforePartial)
			   Url = URLPiece[i].item + partialURL;
		   else
			   Url = partialURL + URLPiece[i].item;
		   
		   boolean result = urlVal.isValid(Url);
		   boolean expected = URLPiece[i].valid;
		   if(result != expected) {
			   System.out.print("X " + Url + " --expected: " + expected + " result: " + result);
			   System.out.print(" --when " + testName + " = \"" + URLPiece[i].item + "\"" + "\n" );
			   testsFailed++;
		   }
	   }
	   System.out.println("\n" + testName + ": " + (URLPiece.length-testsFailed) + "/" + URLPiece.length + " tests passed.");
	   System.out.println();
   }
   
   //ResultPair arrays to be used with runPartTest()

   ResultPair[] testUrlScheme = {
	   new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", true),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false)
   };
	
   ResultPair[] testUrlAuthority = {
	  new ResultPair("www.oregonstate.edu", true),
          new ResultPair("amazon.com", true),
          new ResultPair("www.amazon.net", true),
          new ResultPair("www.amazon.org", true),
          new ResultPair("bbc.co.uk", true),
          new ResultPair("go.uk", true),
          new ResultPair("go.au", true),
          new ResultPair("0.0.0.0", true),
          new ResultPair("255.255.255.255", true),
          new ResultPair("256.256.256.256", false),
          new ResultPair("255.com", true),
          new ResultPair("1.2.3.4.5", false),
          new ResultPair("1.2.3.4.", false),
          new ResultPair("1.2.3", false),
          new ResultPair(".1.2.3.4", false),
          new ResultPair("go.a", false),
          new ResultPair("go.a1a", false),
          new ResultPair("go.cc", true),
          new ResultPair("go.1aa", false),
          new ResultPair("aaa.", false),
          new ResultPair(".aaa", false),
          new ResultPair("aaa", false),
          new ResultPair("", false)
	};
   
	ResultPair[] testUrlPort = {
          new ResultPair(":80", true),
          new ResultPair(":65535", true),
          new ResultPair(":0", true),
          new ResultPair("", true),
          new ResultPair(":-1", false),
          new ResultPair(":65636", false),
          new ResultPair(":656", true),
          new ResultPair(":6563", true),
          new ResultPair(":1000", true),
          new ResultPair(":999", true),
          new ResultPair(":65a", false)
	};
	
	ResultPair[] testPath = {
	      new ResultPair("/test1", true),
	      new ResultPair("/t123", true),
	      new ResultPair("/$23", true),
	      new ResultPair("/..", false),
	      new ResultPair("/../", false),
	      new ResultPair("/test1/", true),
	      new ResultPair("", true),
	      new ResultPair("/test1/file", true),
	      new ResultPair("/..//file", false),
	      new ResultPair("/test1//file", false)
	};

	
	ResultPair[] testUrlQuery = {
	  new ResultPair("?action=view", true),
          new ResultPair("?action=edit&mode=up", true),
          new ResultPair("?", true),
          new ResultPair("", true)
	};
	
	/*public void testDebugger()
	{
		   System.out.println("--------------------STARTING DEBUGGING--------------------");
		   
		   
		   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		   System.out.println(urlVal.isValid("http://bbc.co.uk"));
		   
		   
		   System.out.println("--------------------DEBUGGING FINISHED--------------------");
		   
	}*/
}