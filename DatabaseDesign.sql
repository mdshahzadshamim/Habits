CREATE TABLE habits
(
    date_ymd DATE PRIMARY KEY NOT NULL,
    discrete_maths SMALLINT DEFAULT 0 CHECK (discrete_maths IN (0, 1)),
    leet_code_1 SMALLINT DEFAULT 0 CHECK (leet_code_1 IN (0, 1)),
    systems_design SMALLINT DEFAULT 0 CHECK (systems_design IN (0, 1)),
    leet_code_2 SMALLINT DEFAULT 0 CHECK (leet_code_2 IN (0, 1)),
    cpp SMALLINT DEFAULT 0 CHECK (cpp IN (0, 1)),
    leet_code_3 SMALLINT DEFAULT 0 CHECK (leet_code_3 IN (0, 1))
);