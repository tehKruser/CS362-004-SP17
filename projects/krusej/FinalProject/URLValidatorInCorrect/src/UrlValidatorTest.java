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
	  
	   System.out.println("-------Testing Valid URLs-------");
	   System.out.println("The following urls should all result in 'true'");
	   for(int i = 0; i < goodUrls.length; i++){
		   if(urlVal.isValid(goodUrls[i])){
			   passCount += 1;
		   } else {
			   failCount += 1;
		   }
		   System.out.println(i + ". " + goodUrls[i] + ": " + String.valueOf(urlVal.isValid(goodUrls[i])));
	   }
	   
	   System.out.println("\n-------Testing Invalid URLs-------");
	   System.out.println("The following urls should all result in 'false'");
	   for(int i = 0; i < badUrls.length; i++){
		   if(urlVal.isValid(badUrls[i])){
			   failCount += 1;
		   } else {
			   passCount += 1;
		   }
		   System.out.println(i + ". " + badUrls[i] + ": " + String.valueOf(urlVal.isValid(badUrls[i])));
	   }
	   
	   
	   System.out.println("\nTests Passed: " + passCount);
	   System.out.println("Tests Failed: " + failCount);
   }
   
   
   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
   }
   
   
   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
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
   
   //URLs that are invalid
   String bad1 = new String("http://www.google.com:-1");
   String bad2 = new String("http:/www.google.com");
   String bad3 = new String("http:www.google.com");
   String bad4 = new String("http://www.google.com:3a");
   String bad5 = new String("http://www.google.com/#");
   String bad6 = new String("http://www.google.com/#/file");
   
   String[] goodUrls= { good1, good2, good3, good4, good5, good6, good7, good8, good9};
   String[] badUrls= { bad1, bad2, bad3, bad4, bad5, bad6};
   
}
