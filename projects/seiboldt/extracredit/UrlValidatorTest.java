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

import java.util.Calendar;
import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;


public class UrlValidatorTest extends TestCase {
    
    private static final long thirtySeconds = 30000; //timeout after 30 seconds
    private static final int Rounds = 2000;
    
    private String[] legalSchemes = new String[]{"https://", "http://", "ftp://"};
    private String[] illegalSchemes = new String[]{"http/", "Abht://", "http:/", "://", "", "habit://"};
    private String[] legalHosts = new String[]{"www.google.com", "oregonstate.edu", "facebook.com", "255.255.255.255"};
    private String[] localhost = new String[]{"localhost", "127.0.0.1" };
    private String[] illegalHosts = new String[]{"google.randomness", "", " ", "aaa", "001.112.1.444.5"};
    private String[] legalPorts = new String[]{":80", ":49151", ":0", ""};
    private String[] illegalPorts = new String[]{":-10", ":randomness", "12a"};
    private String[] legalPaths = new String[]{"/allgood", "", "/12345", "/thisworks/", "/this/should/work"};
    private String[] illegalPaths = new String[]{"//bad", ",", "/bad//path", "this(is)bad"};
    private String[] legalQueries = new String[]{"", "?query=parameter"};
    private String[] illegalQueries = new String[]{"a random string with spaces in it", "http://"};
    
    
    // Choose random string from array
    private static String chooseString(Random random, String[] string) {
        int next = random.nextInt(string.length);
        return string[next];
    }
    
    
    public void testIsLegal() {
        
        long theBeginning = Calendar.getInstance().getTimeInMillis();
        long sinceTheBeginning = Calendar.getInstance().getTimeInMillis() - theBeginning;
        
        System.out.println("Starting legal global tests...");
        
        long seed = 0;
        while (sinceTheBeginning < thirtySeconds) {
            
            seed++;
            seed = seed % 1000;
            Random randomLocation = new Random(seed);
            
            UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
            
            for (int i = 0; i < Rounds; i++) {
                String Scheme = chooseString(randomLocation, legalSchemes);
                String Host = chooseString(randomLocation, legalHosts);
                String Ports = chooseString(randomLocation, legalPorts);
                String Paths = chooseString(randomLocation, legalPaths);
                String Query = chooseString(randomLocation, legalQueries);
                String URL = Scheme + Host + Ports + Paths + Query;
                
                /*
                 ResultPair testPair = testScheme[sIndex];
                 boolean result = urlVal.isValidScheme(testPair.item);
                 assertEquals(testPair.item, testPair.valid, result);*/
                
                
                assertTrue(URL, urlVal.isValid(URL));
            }
            
            sinceTheBeginning = (Calendar.getInstance().getTimeInMillis() - theBeginning);
        }
        
        System.out.println("Legal global testing complete.");
    }
    
    
    //Illegal URL tests
    public void testIfAllIsIllegal() {
        
        long theBeginning = Calendar.getInstance().getTimeInMillis();
        long sinceTheBeginning = Calendar.getInstance().getTimeInMillis() - theBeginning;
        
        System.out.println("Starting completely illegal global tests...");
        
        long seed = 0;
        while (sinceTheBeginning < thirtySeconds) {
            
            seed++;
            seed = seed % 1000;
            Random randomLocation = new Random(seed);
            
            UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
            
            for (int i = 0; i < Rounds; i++) {
                String Scheme = chooseString(randomLocation, illegalSchemes);
                String Host = chooseString(randomLocation, illegalHosts);
                String Ports = chooseString(randomLocation, illegalPorts);
                String Paths = chooseString(randomLocation, illegalPaths);
                String Query = chooseString(randomLocation, illegalQueries);
                String URL = Scheme + Host + Ports + Paths + Query;
                
                assertFalse(URL, urlVal.isValid(URL));
            }
            
            sinceTheBeginning = (Calendar.getInstance().getTimeInMillis() - theBeginning);
        }
        
        System.out.println("Completely illegal global testing complete.");
    }
    
    
    //Illegal URL tests
    public void testIfOnlyPartIsIllegal() {
        
        long theBeginning = Calendar.getInstance().getTimeInMillis();
        long sinceTheBeginning = Calendar.getInstance().getTimeInMillis() - theBeginning;
        
        System.out.println("Starting partially illegal global tests...");
        
        long seed = 0;
        while (sinceTheBeginning < thirtySeconds) {
            
            seed++;
            seed = seed % 1000;
            Random randomLocation = new Random(seed);
            
            UrlValidator urlVal = new UrlValidator(legalSchemes, null, UrlValidator.ALLOW_LOCAL_URLS);
            
            //go through all of the rounds
            for (int i = 0; i < Rounds; i++) {
                
                //choose one part of the url that will be illegal
                int partThatIsIllegal = ThreadLocalRandom.current().nextInt(0, 5);
                
                //start by making everything legal
                String Scheme = chooseString(randomLocation, legalSchemes);
                String Host = chooseString(randomLocation, legalHosts);
                String Ports = chooseString(randomLocation, legalPorts);
                String Paths = chooseString(randomLocation, legalPaths);
                String Query = chooseString(randomLocation, legalQueries);
                
                switch (partThatIsIllegal) {
                    case (0):
                        Scheme = chooseString(randomLocation, illegalSchemes);
                        break;
                        
                    case (1):
                        Host = chooseString(randomLocation, illegalHosts);
                        break;
                        
                    case (2):
                        Ports = chooseString(randomLocation, illegalPorts);
                        break;
                        
                    case (3):
                        Paths = chooseString(randomLocation, illegalPaths);
                        break;
                        
                    case (4):
                        Query = chooseString(randomLocation, illegalQueries);
                        break;
                        
                        
                }
                String URL = Scheme + Host + Ports + Paths + Query;
                assertFalse(URL, urlVal.isValid(URL));
            }
            
            sinceTheBeginning = (Calendar.getInstance().getTimeInMillis() - theBeginning);
        }
        
        System.out.println("Partially illegal global testing complete.");
    }
    
    public void testIsLegalLocalhost() {
        
        long theBeginning = Calendar.getInstance().getTimeInMillis();
        long sinceTheBeginning = Calendar.getInstance().getTimeInMillis() - theBeginning;
        
        System.out.println("Starting legal localhost tests...");
        
        long seed = 0;
        while (sinceTheBeginning < thirtySeconds) {
            
            seed++;
            seed = seed % 1000;
            Random randomLocation = new Random(seed);
            
            UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
            
            for (int i = 0; i < Rounds; i++) {
                String Scheme = chooseString(randomLocation, legalSchemes);
                String Host = chooseString(randomLocation, localhost);
                String Ports = chooseString(randomLocation, legalPorts);
                String Paths = chooseString(randomLocation, legalPaths);
                String Query = chooseString(randomLocation, legalQueries);
                String URL = Scheme + Host + Ports + Paths + Query;
                
                assertTrue(URL, urlVal.isValid(URL));
            }
            
            sinceTheBeginning = (Calendar.getInstance().getTimeInMillis() - theBeginning);
        }
        
        System.out.println("Legal localhost testing complete.");
    }
    
    
    //Illegal URL tests
    public void testIfAllIsIllegalLocalhost() {
        
        long theBeginning = Calendar.getInstance().getTimeInMillis();
        long sinceTheBeginning = Calendar.getInstance().getTimeInMillis() - theBeginning;
        
        System.out.println("Starting completely illegal localhost tests...");
        
        long seed = 0;
        while (sinceTheBeginning < thirtySeconds) {
            
            seed++;
            seed = seed % 1000;
            Random randomLocation = new Random(seed);
            
            UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
            
            for (int i = 0; i < Rounds; i++) {
                String Scheme = chooseString(randomLocation, illegalSchemes);
                String Host = chooseString(randomLocation, localhost);
                String Ports = chooseString(randomLocation, illegalPorts);
                String Paths = chooseString(randomLocation, illegalPaths);
                String Query = chooseString(randomLocation, illegalQueries);
                String URL = Scheme + Host + Ports + Paths + Query;
                
                assertFalse(URL, urlVal.isValid(URL));
            }
            
            sinceTheBeginning = (Calendar.getInstance().getTimeInMillis() - theBeginning);
        }
        
        System.out.println("Completely illegal localhost testing complete.");
    }
    
    
    //Illegal URL tests
    public void testIfOnlyPartIsIllegalLocalhost() {
        
        long theBeginning = Calendar.getInstance().getTimeInMillis();
        long sinceTheBeginning = Calendar.getInstance().getTimeInMillis() - theBeginning;
        
        System.out.println("Starting partially illegal localhost tests...");
        
        long seed = 0;
        while (sinceTheBeginning < thirtySeconds) {
            
            seed++;
            seed = seed % 1000;
            Random randomLocation = new Random(seed);
            
            UrlValidator urlVal = new UrlValidator(legalSchemes, null, UrlValidator.ALLOW_LOCAL_URLS);
            
            //go through all of the rounds
            for (int i = 0; i < Rounds; i++) {
                
                //choose one part of the url that will be illegal
                int partThatIsIllegal = ThreadLocalRandom.current().nextInt(0, 5);
                
                //start by making everything legal
                String Scheme = chooseString(randomLocation, legalSchemes);
                String Host = chooseString(randomLocation, localhost);
                String Ports = chooseString(randomLocation, legalPorts);
                String Paths = chooseString(randomLocation, legalPaths);
                String Query = chooseString(randomLocation, legalQueries);
                
                switch (partThatIsIllegal) {
                    case (0):
                        Scheme = chooseString(randomLocation, illegalSchemes);
                        break;
                        
                    case (1):
                        Host = chooseString(randomLocation, illegalHosts);
                        break;
                        
                    case (2):
                        Ports = chooseString(randomLocation, illegalPorts);
                        break;
                        
                    case (3):
                        Paths = chooseString(randomLocation, illegalPaths);
                        break;
                        
                    case (4):
                        Query = chooseString(randomLocation, illegalQueries);
                        break;
                        
                        
                }
                String URL = Scheme + Host + Ports + Paths + Query;
                assertFalse(URL, urlVal.isValid(URL));
            }
            
            sinceTheBeginning = (Calendar.getInstance().getTimeInMillis() - theBeginning);
        }
        
        System.out.println("Patially illegal localhost testing complete.");
    }
    
}