CREATE TABLE habits
(
    date_ymd DATE PRIMARY KEY NOT NULL,
    discrete_maths      SMALLINT DEFAULT 0 CHECK (discrete_maths        BETWEEN 0 AND 1),
    leet_code_1         SMALLINT DEFAULT 0 CHECK (leet_code_1           BETWEEN 0 AND 3),
    systems_design      SMALLINT DEFAULT 0 CHECK (systems_design        BETWEEN 0 AND 1),
    leet_code_2         SMALLINT DEFAULT 0 CHECK (leet_code_2           BETWEEN 0 AND 3),
    computer_networks   SMALLINT DEFAULT 0 CHECK (computer_networks     BETWEEN 0 AND 1),
    leet_code_3         SMALLINT DEFAULT 0 CHECK (leet_code_3           BETWEEN 0 AND 3),
    full_stack          SMALLINT DEFAULT 0 CHECK (full_stack            BETWEEN 0 AND 1),
    algorithms          SMALLINT DEFAULT 0 CHECK (algorithms            BETWEEN 0 AND 1);
);


SELECT discrete_maths, leet_code_1, systems_design, leet_code_2, computer_networks, leet_code_3 FROM habits WHERE date_ymd = CURRENT_DATE;



