-- Keep a log of any SQL queries you execute as you solve the mystery.

-- search description of crimes that happened at the data and street
SELECT description FROM crime_scene_reports
    WHERE year = "2021" AND day = "28"
    AND month = "7" AND street = "Humphrey Street";

-- theft took place at 10:15 am on the bakery. 3 witnesses were interviewed and they mentioned the bakery
-- seach for the interviews done at the day of the theft
SELECT transcript FROM interviews
    WHERE year = "2021" AND day = "28"
    AND month = "7";

-- the thief got in a car in the bakery parking lot. Security footage might show the car that was parked at the time of the crime [10:15am].
-- search for car plates at the time of crime
SELECT activity, license_plate FROM bakery_security_logs
    WHERE year = "2021" AND day = "28" AND month = "7" AND hour = "10" AND minute > "15" AND minute < "30";
-- 8 cars left the bakery parking lot that time 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55

-- the thief was at the atm that morning wirthdrawing some money at Leggett Street
SELECT account_number, amount FROM atm_transactions
    WHERE year = "2021" AND day = "28" AND month = "7" AND transaction_type = "withdraw" AND atm_location = "Leggett Street";
-- we have the numbers of people who withdrawed money on that atm at that day, there were 8 withdraws
-- we should now get the name of the proprietary of each of these accounts
SELECT DISTINCT(people.name), people.passport_number, people.license_plate, people.phone_number FROM people
    JOIN bank_accounts ON bank_accounts.person_id = people.id
    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
    WHERE atm_transactions.account_number IN (SELECT atm_transactions.account_number FROM atm_transactions
        WHERE year = "2021" AND day = "28" AND month = "7" AND transaction_type = "withdraw" AND atm_location = "Leggett Street");
--of this people the only ones who match the same plate as the bakery parking loot are Bruce[94KL13X], Diana[322W7JE], Iman[L93JTIZ], Luca[4328GD8]

-- the thief called someone and talked for less than a minute, they planned to take the earliest flight out of fiftyville the day after, he asked for the person to buy the flight tickets
-- check phone calls and check name of the caller
SELECT name FROM people
    WHERE phone_number IN (SELECT caller FROM phone_calls
        WHERE month = "7" AND year = "2021" AND day = "28" AND duration < "60");
-- the people who are suspects that made a call with this specifications are Bruce, Diana

-- check earliest flight leaving fiftyville the day after
SELECT id, destination_airport_id, hour, minute FROM flights
    WHERE month = "7" AND day = "29" AND year = "2021" AND origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour;

--Earliest flight left at 8h20minutes of the day after the theft (29 july 2021) - we should check the manifest
SELECT passport_number FROM passengers
    JOIN flights ON flights.id = passengers.flight_id
    WHERE month = "7" AND day = "29" AND year = "2021" AND hour = "8" AND minute = "20" AND origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville");

-- crisscross passport_number with license plates and phone number [we can only have two license plates of suspects 94KL13X, 4328GD8]
SELECT name, license_plate, phone_number FROM people
    WHERE passport_number IN (SELECT passport_number FROM passengers
        JOIN flights ON flights.id = passengers.flight_id
        WHERE month = "7" AND day = "29" AND year = "2021" AND hour = "8" AND minute = "20" AND origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville"))
    AND phone_number IN (SELECT caller FROM phone_calls
        WHERE month = "7" AND year = "2021" AND day = "28" AND duration < "60");
--of the suspects, the ones leaving town in the flight that the thief will be also leaving is only bruce which phone_number is 367 555 5533 - the thief is bruce

SELECT full_name, city FROM airports
    JOIN flights ON flights.destination_airport_id = airports.id
    WHERE origin_airport_id IN (SELECT airports.id FROM airports WHERE airports.city = "Fiftyville")
    AND year = "2021" AND day = "29" AND month = "7" AND hour = "8" AND minute = "20";
-- the thief went to La Guardia Airport in New York City

-- check who the thief helper was based on phonecalls
SELECT name, phone_number FROM people
        WHERE phone_number IN (SELECT receiver FROM phone_calls
            WHERE caller = "(367) 555-5533" AND month = "7" AND year = "2021" AND day = "28" AND duration < "60");
--the helper was robin