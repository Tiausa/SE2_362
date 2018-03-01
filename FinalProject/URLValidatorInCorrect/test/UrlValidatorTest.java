

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {

	   boolean testStatus = false, expectedStatus = false;
	   int runs = 0, bugs = 0, failures = 0, successes = 0;
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   
	   while( true ) {
		   
		   // Get a valid set of portions for a valid url
		   // Need arrays for a set of valid combinations to test
		   String scheme = "";
		   String authority = "";
		   String port = "";
		   String path = "";
		   String query = "";
		   
		   // Build a valid url to test
		   String url = scheme + authority + port + path + query;
		   
		   for( int idx = 0; idx < 7; idx++ ) {
			   switch (idx) {
				   case 0:
					  // Test base matches
					  expectedStatus = true;
					  break;
				   case 1:
					   // Test isValidScheme
					   
					   expectedStatus = false;
					   break;
				   case 2:
					   // Test isValidAuthority
					   
					   expectedStatus = false;
					   break;
				   case 3:
					   // Test isValidPath
					   
					   expectedStatus = false;
					   break;
				   case 4:
					   // Test isValidQuery
					   
					   expectedStatus = false;
					   break;
				   case 5:
					   // Test isValidFragment
					   
					   expectedStatus = false;
					   break;
				   case 6:
					   // Test random combination of invalid portions
					   
					   expectedStatus = false;
					   break;
				   default:
					   break;
			   }

			   // Get status returned
			   testStatus = urlVal.isValid( url );
			   
			   if( testStatus == expectedStatus ) {
				   successes++;
			   } else {
				   System.out.println( "[BUG OCCURED] URL: " + url );
				   failures++;
			   }
						  
			  
		   }
		   
		   if ( successes != 1 && failures != 6 ) {
			   // Unexpected result returned
			   bugs++;
		   }
		   
		   
		   successes = 0;
		   failures = 0;
		   
		   runs++;
		   if( runs > 100 ) { break; }
		   
	   }
	   

   }
   


}
