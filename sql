CREATE TABLE IF NOT EXISTS player_bank (player text , currency text ,amount numeric(21,4) ,CONSTRAINT account_unique unique(player, currency) );
CREATE TABLE IF NOT EXISTS history (from_name text , to_name text , from_value numeric(21,4),to_value numeric(21,4) , from_currency text, to_currency text , note text);
CREATE TABLE IF NOT EXISTS land (x1 int , z1 int , x2 int ,z2 int, id serial , land_owner text);
CREATE TABLE IF NOT EXISTS land_share (id int, player text);