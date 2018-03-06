

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
   
   
   
   // Programmatic Testing 
 
   
   public class TestURL {
	   // Parts of the TestURL
	   private String scheme = "";
	   private String authority = "";
	   private String port = "";
	   private String path = "";
	   private String query = "";
	   // Expected validity of the TestURL
	   private Boolean validity = true;
	   
	   // Our TestURL Good Options
	   public String[] goodSchemes = { "http://", "https://", "ftp://", "h3t://", "" };
	   public String[] goodAuthorities = { "www.google.com", "www.icann.org", "www.oregonstate.edu", "oregonstate.edu", "secure.oregonstate.com" };
	   public String[] goodPorts = { ":80", ":8080", ":20", ":0", "" };
	   public String[] goodPaths = { "/path", "/path/subpath", "/otherpath/", "/123abc$", "" };
	   public String[] goodQueries = { "?search=term", "?search=term&page=1", "?search=one+two", "?action=nothing", "???" };
	   
	   // Our TestURL Bad Options
	   public String[] badSchemes = { "abc://", "://", "http:/", "<#>://", "://http" };
	   public String[] badAuthorities = {  "wwwwww.oregon.state.eedduu", "edu.oregonstate.", "oregonstate..edu", "www.com", "" };
	   public String[] badPorts = {  ":99999", ":-99999", ":abc", ":###", ":0a1b" };
	   public String[] badPaths = { "\\path", "../", "/path/..", "/../../path", "/../path/.." };
	   public String[] badQueries = { "?search=/?/", "!search=&term", "term=search?", "?search=termpage=one", "search?=term" };
	   
	   // Base Constructor
	   public TestURL() {
		   super();
		   
		   // Set the URL
		   scheme = goodSchemes[ (int)( Math.random() * goodSchemes.length ) ];
		   authority = goodAuthorities[ (int)( Math.random() * goodAuthorities.length ) ];
		   port = goodPorts[ (int)( Math.random() * goodPorts.length ) ];
		   path = goodPaths[ (int)( Math.random() * goodPaths.length ) ];
		   query = goodQueries[ (int)( Math.random() * goodQueries.length ) ];
		  
		   validity = true;
		   
	   }
	   
	   
	   // Base getters
	   public String getScheme() { return scheme; }
	   public String getAuthority() { return authority; }
	   public String getPort() { return port; }
	   public String getPath() { return path; }
	   public String getQuery() { return query; }
	   public Boolean getValidity() { return validity; }
	   
	   // Get TestURL as URL string
	   public String toString() {
		   return scheme + authority + port + path + query;
	   }
	   
	   // Makes a selected part of the TestURL invalid
	   public String makeBad(int option) {
		   return scheme + authority + port + path + query;
	   }
	   
   }
   
   public String getURLPart(String[] options ) {
	   int ran = (int)( Math.random() * 10 );
	   return options[ran];
   }
   
   public void testIsValid()
   {

	   boolean testStatus = false, expectedStatus = false;
	   int runs = 0, bugs = 0, failures = 0, successes = 0;	   	   
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   
	   while( true ) {
		   
		   // Build a new TestURL
		   TestURL tester = new TestURL();
		   
		   // Get the TestURL string
		   String url = tester.toString();
		   
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
