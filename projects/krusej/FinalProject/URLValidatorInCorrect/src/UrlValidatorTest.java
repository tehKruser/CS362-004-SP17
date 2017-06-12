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

   
   
   public void testManualTest()
   {
	   int failCount = 0;
	   int passCount = 0;
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	  
	   //urlVal.isValid("http://www.google.com:1000");	// check string of choice here with breakpoint to trace source of bug in debug
	   
	   System.out.println("-------Testing Valid URLs-------");
	   System.out.println("The following urls should all result in 'true'");
	   for(int i = 0; i < goodUrls.length; i++){
		   if(urlVal.isValid(goodUrls[i])){
			   passCount += 1;
		   } else {
			   failCount += 1;
		   }
		   
		   System.out.printf("%-4s %-43s %-10s\n", String.valueOf(i+1), goodUrls[i], String.valueOf(urlVal.isValid(goodUrls[i])));
	   }
	   
	   System.out.println("\n-------Testing Invalid URLs-------");
	   System.out.println("The following urls should all result in 'false'");
	   for(int i = 0; i < badUrls.length; i++){
		   if(urlVal.isValid(badUrls[i])){
			   failCount += 1;
		   } else {
			   passCount += 1;
		   }
		   
		   System.out.printf("%-4s %-43s %-10s\n", String.valueOf(i+1), badUrls[i], String.valueOf(urlVal.isValid(badUrls[i])));
	   }
	   
	   
	   System.out.println("\nTests Passed: " + passCount);
	   System.out.println("Tests Failed: " + failCount);
   }
   
   
    //Start of Project B - Section 2 - Partion Tests
    //-------------------------------------------------------------------------------------------------------------------------------
   
   public void testYourFirstPartition()
   {
	   int count = 0;									//variable to count the # of failed tests
	   String testURL = "";								//variable to store our test URL
	   String testName = "testUrlScheme";				//variable to store our partition test's name
	   
	   UrlValidator url = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);		//UrlValidator object
	   
	   startPrint(testName);
	   
	   //iterate through the partition array and build testURLs
	   for(int i = 0; i < this.testUrlScheme.length; i++)
	   {
		   testURL = "";
		   
		   testURL = testURL + this.testUrlScheme[i].item;
		   testURL = testURL + "www.theverge.com";
		   
		   //if isValid() returns a value different than the expected value; ie. "Assert" the values are equal
		   if(url.isValid(testURL) != this.testUrlScheme[i].valid)
		   {
			   	System.out.println("isValid() result:  " + url.isValid(testURL) + "   " +
					   "\t expected result: " + this.testUrlScheme[i].valid +  "   " +
					   "\t testUrlScheme: '" + this.testUrlScheme[i].item + "'   " );
			   
			   count = count + 1;
		   }
	   }
	   
	   endPrint(count, testName);
   }
   
   
   public void testYourSecondPartition(){
	   int count = 0;							    	//variable to count the # of failed tests
	   String testURL = "http://";				    	//variable to store our test URL
	   String testName = "testUrlAuthority";			//variable to store our partition test's name
	   
	   UrlValidator url = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);		//UrlValidator object
	   
	   startPrint(testName);
	   
	   //iterate through the partition array and build testURLs
	   for(int i = 0; i < this.testUrlAuthority.length; i++)
	   {
		   testURL = "http://";
		   
		   testURL = testURL + this.testUrlAuthority[i].item;
		   
		   //if isValid() returns a value different than the expected value; ie. "Assert" the values are equal
		   if(url.isValid(testURL) != this.testUrlAuthority[i].valid)
		   {
			   System.out.println("isValid() result:  " + url.isValid(testURL) + "   " +
					   "\t expected result: " + this.testUrlAuthority[i].valid +  "   " +
					   "\t testUrlAuthority: '" + this.testUrlAuthority[i].item + "'   " );
			   
			   count = count + 1;
		   }
	   }
	   
	   endPrint(count, testName);
   }
   
   
   public void testYourThirdPartition(){
	   int count = 0;										//variable to count the # of failed tests
	   String testURL = "http://www.theverge.com";			//variable to store our test URL
	   String testName = "testUrlPort";				   		//variable to store our partition test's name
	   
	   UrlValidator url = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);		//UrlValidator object
	   
	   startPrint(testName);
	   
	   //iterate through the partition array and build testURLs
	   for(int i = 0; i < this.testUrlPort.length; i++)
	   {
		   testURL = "http://www.theverge.com";
		   
		   testURL = testURL + this.testUrlPort[i].item;
		   
		   //if isValid() returns a value different than the expected value; ie. "Assert" the values are equal
		   if(url.isValid(testURL) != this.testUrlPort[i].valid)
		   {
			   System.out.println("isValid() result:  " + url.isValid(testURL) + "   " +
					   "\t expected result: " + this.testUrlPort[i].valid +  "   " +
					   "\t testUrlPort: '" + this.testUrlPort[i].item + "'   " );
			   
			   count = count + 1;
		   }
	   }
	   
	   endPrint(count, testName);
   }
   
   
   public void testYourFourthPartition(){
	   int count = 0;										//variable to count the # of failed tests
	   String testURL = "http://www.theverge.com";			//variable to store our test URL
	   String testName = "testUrlPath";						//variable to store our partition test's name
	   
	   UrlValidator url = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);		//UrlValidator object
	   
	   startPrint(testName);
	   
	   //iterate through the partition array and build testURLs
	   for(int i = 0; i < this.testUrlPath.length; i++)
	   {
		   testURL = "http://www.theverge.com";
		   
		   testURL = testURL + this.testUrlPath[i].item;
		   
		   //if isValid() returns a value different than the expected value; ie. "Assert" the values are equal
		   if(url.isValid(testURL) != this.testUrlPath[i].valid)
		   {
			   System.out.println("isValid() result:  " + url.isValid(testURL) + "   " +
					   "\t expected result: " + this.testUrlPath[i].valid +  "   " +
					   "\t testUrlPath: '" + this.testUrlPath[i].item + "'   " );
			   
			   count = count + 1;
		   }
	   }
	   
	   endPrint(count, testName);
   }
   
   //Prints header information for the partition tests
   public void startPrint(String testName)
   {
	   System.out.println("");
	   System.out.println("Failed " + testName + " test(s):");
	   System.out.println("-----------------------------");   
   }
   
   //Prints the # of failed tests (if any) for the partition tests
   public void endPrint(int count, String testName)
   {
	   System.out.println("-----------------------------");
	   if(count == 0)
	   {
		   System.out.print("No failed tests!");
		   System.out.println("");
		   System.out.println("");
	   }
	   else
	   {
		   System.out.println("# of failed " + testName + " test(s): " + count);
		   System.out.println("");
	   }
   }
   
   //-------------------------------------------------------------------------------------------------------------------------------
   //End of Project B - Section 2 - Partion Tests
   
   
   //Start of the Unit Test --------------------------------------------------------------------------------------------------------
   /*Third, do programming based testing. Write few unit test cases.
    * You can have some sort of loop in your unit test and test different URL with each instance of the loop.
    * Something very similar to testIsValid() but your own logic and idea. 
    * Even a single test will be sufficient if you write it like testIsValid() method
    * */
    
    //Int array that allows the user to define the number of ResultPairs from each partition they would like to test
    int[] testUrlLimits = {0,0,0,0,0};
    
    //Method that corrext the limit values
    //if less than partition.length set to 0
    //if greater than partition.length set to partition.length
    public int validLimits(int[] testLimitValues, int index){
    	if(index == 0){
    		if(testLimitValues[index] < 0){
    			return 0;
    		}
    		if(testLimitValues[index] > testUrlScheme.length){
    			return testUrlScheme.length;
    		}
    	}
    	if(index == 1){
    		if(testLimitValues[index] < 0){
    			return 0;
    		}
    		if(testLimitValues[index] > testUrlAuthority.length){
    			return testUrlAuthority.length;
    		}
    	}
		if(index == 2){
    		if(testLimitValues[index] < 0){
    			return 0;
    		}
    		if(testLimitValues[index] > testUrlPort.length){
    			return testUrlPort.length;
    		}
    	}
    	if(index == 3){
    		if(testLimitValues[index] < 0){
    			return 0;
    		}
    		if(testLimitValues[index] > testUrlPath.length){
    			return testUrlPath.length;
    		}
    	}
    	if(index == 4){
    		if(testLimitValues[index] < 0){
    			return 0;
    		}
    		if(testLimitValues[index] > testUrlQuery.length){
    			return testUrlQuery.length;
    		}
    	}
    	return 0;
    	
    }
    
    //REFERENCE - https://github.com/aburasa/CS362-004-SP17/blob/master/FinalProject/URLValidatorCorrect/test/UrlValidatorTest.java
    //based on the testIsValid method; which is an ideal and efficient method
    //rather than using multiple helper methods to assemble and construct the url, quad nested loops were implemented
    //user can use a int array to limit the amount of urls being tested
	public void testIsValid(int[] testUrlLimitsValue){
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
  		
		int totalPassed = 0;
		int totalFailed = 0;
		
		int[] validatedLimits = {0,0,0,0,0};
		
		//validate limit values for total number of tests
		for(int h = 0; h < testUrlLimitsValue.length;h++){
			validatedLimits[h] = validLimits(testUrlLimits, h);
		}
		
		
		for (int i = 0; i < validatedLimits[0]; i++){
			for(int j = 0; j < validatedLimits[1]; j++){
				for(int k = 0; k < validatedLimits[2]; k++){
					for(int l = 0; l < validatedLimits[3]; l++){
						for(int m = 0; m < validatedLimits[4]; m++){
							
							StringBuffer testBuffer = new StringBuffer();
							boolean expected = true;
							
							ResultPair schemePart = testUrlScheme[i];
							ResultPair authorityPart = testUrlAuthority[j];
							ResultPair portPart = testUrlPort[k];
							ResultPair pathPart = testUrlPath[l];
							ResultPair queryPart = testUrlQuery[m];
							
							if((schemePart.valid == false)||(authorityPart.valid == false) ||(portPart.valid == false) || (pathPart.valid == false) || (queryPart.valid == false)){
								expected = false;
							}
							
							testBuffer.append(schemePart.item);
							testBuffer.append(authorityPart.item);
							testBuffer.append(portPart.item);
							testBuffer.append(pathPart.item);
							testBuffer.append(queryPart.item);
							
							String testUrl = testBuffer.toString();
							boolean result = urlVal.isValid(testUrl);
							
							if(result == expected){
								System.out.println(testUrl + " >>> Passed\n");
								totalPassed++;
							}
							else{
								System.out.println(testUrl + " >>> Failed\n");
								totalFailed++;
							}
						}	
					}	
				}
			}
		}
		System.out.println("Total Passed = "+totalPassed+"\nTotalFailed = "+ totalFailed);
   }
   
   
   /*
    public void main()
   {
   	   int[] testLimit = {testUrlScheme.length,testUrlAuthority.length,testUrlPort.length,testUrlPath.length, testUrlQuery.length}
	   testIsValid(testLimit);
   }
   */
   
   
   //End of the Unit Tests----------------------------------------------------------------------------------------------------------
   
  
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   
   //----- URLs for manual testing
   // URLs that are valid
   String good1 = new String("http://www.google.com");
   String good2 = new String("http://www.google.com/");
   String good3 = new String("http://www.google.com:0");
   String good4 = new String("http://www.google.com:80");
   String good5 = new String("http://www.google.com:65535");
   String good6 = new String("http://www.google.com/test1");
   String good7 = new String("http://www.google.com?action=view");
   String good8 = new String("http://www.google.com/test1?action=view");
   String good9 = new String("http://www.google.com/test1/file");
   String good10 = new String("http://www.google.com:999");
   String good11 = new String("http://www.google.com:1000");
   String good12 = new String("ftp://www.google.com");
   String good13 = new String("h3t://www.google.com");
   String good14 = new String("http://255.255.255.255");
   String good15 = new String("http://0.0.0.0");
   
   //URLs that are invalid
   String bad1 = new String("http://www.google.com:-1");
   String bad2 = new String("http:/www.google.com");
   String bad3 = new String("http:www.google.com");
   String bad4 = new String("http://www.google.com:3a");
   String bad5 = new String("http://www.google.com/..");
   String bad6 = new String("http://www.google.com/test1//file");
   String bad7 = new String("://www.google.com");
   String bad8 = new String("http://256.256.256.256");
   String bad9 = new String("http://1.2.3.4.5");
   String bad10 = new String("3ht://www.google.com");
   String bad11 = new String("http://www.google.com?action==view");
   
   String[] goodUrls= { good1, good2, good3, good4, good5, good6, good7, good8, good9, good10, good11, good12, good13, good14, good15};
   String[] badUrls= { bad1, bad2, bad3, bad4, bad5, bad6, bad7, bad8, bad9, bad10, bad11};
   
   /*-----------------------------------------------------
   //Partions for partition tests - Broken into the 4 parts of a URL: Scheme, Authority, Port and Path
   -------------------------------------------------------*/
   
   //Scheme partitions for url tests
   ResultPair[] testUrlScheme = {new ResultPair("http://", true),
	  new ResultPair("ftp://", true),
	  new ResultPair("https://", true),
	  new ResultPair("http:/", false),
	  new ResultPair("http:", false),
	  new ResultPair("http/", false),
	  new ResultPair("ip//", false),
	  new ResultPair("://", false),
	  new ResultPair("//", false),
	  new ResultPair("", true)
   };
	
	//Authority partitions for url tests
	ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
	  new ResultPair("io.draw", true),
	  new ResultPair("twitch.tv", true),
	  new ResultPair("0.0.0.0", true),
	  new ResultPair("8.8.8.8", true),
	  new ResultPair("255.255.255.255", true),
	  new ResultPair("256.256.256.256", false),
	  new ResultPair("8.com", true),
	  new ResultPair("9.8.7.6.5", false),
	  new ResultPair("1.2.3.4.", false),
	  new ResultPair("1.2.3", false),
	  new ResultPair(".8.8.8.8", false),
	  new ResultPair("-1.-1.-1.-1", false),
	  new ResultPair(".8.8.8.-1", false),
	  new ResultPair("theverge.z", false),
	  new ResultPair("us.gov", true),
	  new ResultPair("amazon.eu", true),
	  new ResultPair("twitch.", false),
	  new ResultPair(".edu", false),
	  new ResultPair("google", false),
	  new ResultPair("", false)
	};
	
	//Port partitions for url tests
	ResultPair[] testUrlPort = {new ResultPair(":80", true),
	  new ResultPair(":8080", true),
	  new ResultPair(":8008", true),
	  new ResultPair(":65535", true),
	  new ResultPair(":443", true),
	  new ResultPair(":21", true),
	  new ResultPair(":65636", false),
	  new ResultPair(":0", true),
	  new ResultPair(":-1", false),
	  new ResultPair(":abc", false),
	  new ResultPair(":/", false),
	  new ResultPair("", true)
	};
	
	//Path partitions for url tests
	ResultPair[] testUrlPath = {new ResultPair("/test1", true),
      new ResultPair("/index", true),
      new ResultPair("/main_page/", true),
      new ResultPair("/&dog", true),
      new ResultPair("/?&dog", false),
      new ResultPair("/?animal=dog", false),
      new ResultPair("/search?animal=dog", true),
      new ResultPair("/..", false),
      new ResultPair("/../", false),
      new ResultPair("/index/main_page", true),
      new ResultPair("/..//index", false),
      new ResultPair("/index//main_page", false),
      new ResultPair("", true)
	};
	
	//REFERENCE - https://github.com/aburasa/CS362-004-SP17/blob/master/FinalProject/URLValidatorCorrect/test/UrlValidatorTest.java - Lines 408 - 411
	//
	ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
                              new ResultPair("?action=edit&mode=up", true),
                              new ResultPair("", true)
	 };
   
}
