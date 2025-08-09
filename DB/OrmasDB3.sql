--
-- PostgreSQL database dump
--

-- Dumped from database version 9.5.16
-- Dumped by pg_dump version 9.5.5

-- Started on 2022-04-17 15:28:04

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 7 (class 2615 OID 228979)
-- Name: OrmasSchema; Type: SCHEMA; Schema: -; Owner: postgres
--

CREATE SCHEMA "OrmasSchema";


ALTER SCHEMA "OrmasSchema" OWNER TO postgres;

--
-- TOC entry 3692 (class 0 OID 0)
-- Dependencies: 7
-- Name: SCHEMA "OrmasSchema"; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON SCHEMA "OrmasSchema" IS 'Ormas application schema';


--
-- TOC entry 1 (class 3079 OID 12355)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 3696 (class 0 OID 0)
-- Dependencies: 1
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = "OrmasSchema", pg_catalog;

--
-- TOC entry 473 (class 1255 OID 228980)
-- Name: getcurrentdate(); Type: FUNCTION; Schema: OrmasSchema; Owner: postgres
--

CREATE FUNCTION getcurrentdate() RETURNS text
    LANGUAGE plpgsql IMMUTABLE
    AS $$
DECLARE 
    currentdate text;
BEGIN
 currentdate := to_char(now()::timestamp(0), 'dd.MM.yyyy hh24:mm');
 return currentdate;
END;
$$;


ALTER FUNCTION "OrmasSchema".getcurrentdate() OWNER TO postgres;

--
-- TOC entry 182 (class 1259 OID 228981)
-- Name: acc_seq; Type: SEQUENCE; Schema: OrmasSchema; Owner: postgres
--

CREATE SEQUENCE acc_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    MAXVALUE 999999999
    CACHE 1;


ALTER TABLE acc_seq OWNER TO postgres;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 183 (class 1259 OID 228983)
-- Name: access_items; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE access_items (
    access_item_id integer NOT NULL,
    access_item_eng character varying(30) NOT NULL,
    access_item_ru character varying(30) NOT NULL,
    access_division character varying(20) NOT NULL
);


ALTER TABLE access_items OWNER TO postgres;

--
-- TOC entry 184 (class 1259 OID 228986)
-- Name: access_items_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW access_items_view AS
 SELECT access_items.access_item_id,
    access_items.access_item_eng,
    access_items.access_item_ru AS access_iterm_ru,
    access_items.access_division
   FROM access_items;


ALTER TABLE access_items_view OWNER TO postgres;

--
-- TOC entry 185 (class 1259 OID 228990)
-- Name: accesses; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE accesses (
    access_id integer NOT NULL,
    role_id integer NOT NULL,
    access_item_id integer NOT NULL
);


ALTER TABLE accesses OWNER TO postgres;

--
-- TOC entry 186 (class 1259 OID 228993)
-- Name: roles; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE roles (
    role_id integer NOT NULL,
    role_code character varying(20) NOT NULL,
    role_name character varying(50) NOT NULL,
    comment character varying(100)
);


ALTER TABLE roles OWNER TO postgres;

--
-- TOC entry 187 (class 1259 OID 228996)
-- Name: accesses_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW accesses_view AS
 SELECT accesses.access_id,
    r.role_name,
    a.access_item_eng,
    a.access_item_ru,
    a.access_division,
    accesses.role_id,
    accesses.access_item_id
   FROM ((accesses
     JOIN roles r ON ((r.role_id = accesses.role_id)))
     JOIN access_items a ON ((a.access_item_id = accesses.access_item_id)));


ALTER TABLE accesses_view OWNER TO postgres;

--
-- TOC entry 188 (class 1259 OID 229000)
-- Name: account_change_log; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE account_change_log (
    account_change_log_id integer NOT NULL,
    account_id integer NOT NULL,
    account_number character varying(20) NOT NULL,
    start_balance numeric(20,3),
    current_balance numeric(20,3),
    log_date timestamp without time zone,
    user_id integer,
    operation_id integer
);


ALTER TABLE account_change_log OWNER TO postgres;

--
-- TOC entry 189 (class 1259 OID 229003)
-- Name: account_change_log_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW account_change_log_view AS
 SELECT account_change_log.account_change_log_id,
    account_change_log.account_id,
    account_change_log.account_number,
    account_change_log.start_balance,
    account_change_log.current_balance,
    to_char(account_change_log.log_date, 'dd.MM.yyyy hh24:mi'::text) AS log_date,
    account_change_log.user_id,
    account_change_log.operation_id
   FROM account_change_log;


ALTER TABLE account_change_log_view OWNER TO postgres;

--
-- TOC entry 190 (class 1259 OID 229007)
-- Name: account_history; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE account_history (
    account_history_id integer NOT NULL,
    account_id integer NOT NULL,
    account_number character varying(20) NOT NULL,
    start_balance numeric(20,3),
    current_balance numeric(20,3),
    from_date date,
    till_date date
);


ALTER TABLE account_history OWNER TO postgres;

--
-- TOC entry 191 (class 1259 OID 229010)
-- Name: account_history_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW account_history_view AS
 SELECT account_history.account_history_id,
    account_history.account_id,
    account_history.account_number,
    account_history.start_balance,
    account_history.current_balance,
    account_history.from_date,
    account_history.till_date
   FROM account_history;


ALTER TABLE account_history_view OWNER TO postgres;

--
-- TOC entry 192 (class 1259 OID 229014)
-- Name: account_type; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE account_type (
    account_type_id integer NOT NULL,
    account_type_name character varying(50) NOT NULL,
    account_type_number integer NOT NULL,
    comment character varying(100)
);


ALTER TABLE account_type OWNER TO postgres;

--
-- TOC entry 193 (class 1259 OID 229017)
-- Name: account_type_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW account_type_view AS
 SELECT account_type.account_type_id,
    account_type.account_type_name,
    account_type.account_type_number,
    account_type.comment
   FROM account_type;


ALTER TABLE account_type_view OWNER TO postgres;

--
-- TOC entry 194 (class 1259 OID 229021)
-- Name: accountable; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE accountable (
    employee_id integer NOT NULL,
    information character varying(200)
);


ALTER TABLE accountable OWNER TO postgres;

--
-- TOC entry 195 (class 1259 OID 229024)
-- Name: accountable_approvement; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE accountable_approvement (
    accountable_approvement_id integer NOT NULL,
    approve_date timestamp without time zone,
    director_id integer,
    accontant_id integer,
    accountable_document_id integer
);


ALTER TABLE accountable_approvement OWNER TO postgres;

--
-- TOC entry 196 (class 1259 OID 229027)
-- Name: accountable_approvement_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW accountable_approvement_view AS
 SELECT accountable_approvement.accountable_approvement_id,
    to_char(accountable_approvement.approve_date, 'dd.MM.yyyy hh24:mm'::text) AS approve_date,
    accountable_approvement.director_id,
    accountable_approvement.accontant_id,
    accountable_approvement.accountable_document_id
   FROM accountable_approvement;


ALTER TABLE accountable_approvement_view OWNER TO postgres;

--
-- TOC entry 197 (class 1259 OID 229031)
-- Name: accountable_document_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE accountable_document_list (
    accountable_document_list_id integer NOT NULL,
    accountable_document_id integer,
    expense_document_id integer
);


ALTER TABLE accountable_document_list OWNER TO postgres;

--
-- TOC entry 3697 (class 0 OID 0)
-- Dependencies: 197
-- Name: COLUMN accountable_document_list.accountable_document_id; Type: COMMENT; Schema: OrmasSchema; Owner: postgres
--

COMMENT ON COLUMN accountable_document_list.accountable_document_id IS '
';


--
-- TOC entry 198 (class 1259 OID 229034)
-- Name: accountable_document_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW accountable_document_list_view AS
 SELECT accountable_document_list.accountable_document_list_id,
    accountable_document_list.accountable_document_id,
    accountable_document_list.expense_document_id
   FROM accountable_document_list;


ALTER TABLE accountable_document_list_view OWNER TO postgres;

--
-- TOC entry 199 (class 1259 OID 229038)
-- Name: accountable_documents; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE accountable_documents (
    accountable_document_id integer NOT NULL,
    document_date timestamp without time zone,
    value numeric(20,3),
    expense_assignment character varying(300),
    accountable_id integer,
    status_id integer
);


ALTER TABLE accountable_documents OWNER TO postgres;

--
-- TOC entry 200 (class 1259 OID 229041)
-- Name: accountable_documents_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW accountable_documents_view AS
 SELECT accountable_documents.accountable_document_id,
    to_char(accountable_documents.document_date, 'dd.MM.yyyy hh24:mm'::text) AS document_date,
    accountable_documents.value,
    accountable_documents.expense_assignment,
    accountable_documents.accountable_id,
    accountable_documents.status_id
   FROM accountable_documents;


ALTER TABLE accountable_documents_view OWNER TO postgres;

--
-- TOC entry 201 (class 1259 OID 229045)
-- Name: accountable_entries; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE accountable_entries (
    accountable_entry_id integer NOT NULL,
    debit_account_id integer,
    debit_subaccount_id integer,
    value numeric(20,3),
    credit_account_id integer,
    credit_subaccount_id integer,
    accountable_document_id integer
);


ALTER TABLE accountable_entries OWNER TO postgres;

--
-- TOC entry 202 (class 1259 OID 229048)
-- Name: accountable_entries_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW accountable_entries_view AS
 SELECT accountable_entries.accountable_entry_id,
    accountable_entries.debit_account_id,
    accountable_entries.debit_subaccount_id,
    accountable_entries.value,
    accountable_entries.credit_account_id,
    accountable_entries.credit_subaccount_id,
    accountable_entries.accountable_document_id
   FROM accountable_entries;


ALTER TABLE accountable_entries_view OWNER TO postgres;

--
-- TOC entry 203 (class 1259 OID 229052)
-- Name: accountable_payment; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE accountable_payment (
    accountable_payment_id integer NOT NULL,
    accountable_document_id integer,
    payment_id integer
);


ALTER TABLE accountable_payment OWNER TO postgres;

--
-- TOC entry 204 (class 1259 OID 229055)
-- Name: accountable_payment_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW accountable_payment_view AS
 SELECT accountable_payment.accountable_payment_id,
    accountable_payment.accountable_document_id,
    accountable_payment.payment_id
   FROM accountable_payment;


ALTER TABLE accountable_payment_view OWNER TO postgres;

--
-- TOC entry 205 (class 1259 OID 229059)
-- Name: accountable_transaction; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE accountable_transaction (
    accountable_transaction_id integer NOT NULL,
    residual_value numeric(20,3),
    total_value numeric(20,3),
    spent_value numeric(20,3),
    difference_value numeric(20,3),
    accountable_document_id integer
);


ALTER TABLE accountable_transaction OWNER TO postgres;

--
-- TOC entry 206 (class 1259 OID 229062)
-- Name: accountable_transaction_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW accountable_transaction_view AS
 SELECT accountable_transaction.accountable_transaction_id,
    accountable_transaction.residual_value,
    accountable_transaction.total_value,
    accountable_transaction.spent_value,
    accountable_transaction.difference_value,
    accountable_transaction.accountable_document_id
   FROM accountable_transaction;


ALTER TABLE accountable_transaction_view OWNER TO postgres;

--
-- TOC entry 207 (class 1259 OID 229066)
-- Name: users; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE users (
    user_id integer NOT NULL,
    user_email character varying(30) NOT NULL,
    user_name character varying(40) NOT NULL,
    user_surname character varying(50),
    user_phone character varying(20),
    user_address character varying(50),
    role_id integer NOT NULL,
    password character varying(30),
    activated boolean
);


ALTER TABLE users OWNER TO postgres;

--
-- TOC entry 208 (class 1259 OID 229069)
-- Name: accountable_veiw; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW accountable_veiw AS
 SELECT users.user_id,
    users.user_name,
    users.user_surname,
    accountable.information,
    users.user_phone,
    users.user_address,
    ( SELECT roles.role_name
           FROM roles
          WHERE (roles.role_id = users.role_id)) AS role_name
   FROM (accountable
     JOIN users ON ((users.user_id = accountable.employee_id)));


ALTER TABLE accountable_veiw OWNER TO postgres;

--
-- TOC entry 209 (class 1259 OID 229073)
-- Name: accountable_withdrawal; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE accountable_withdrawal (
    accountable_withdrawal_id integer NOT NULL,
    accountable_document_id integer,
    withdrawal_id integer
);


ALTER TABLE accountable_withdrawal OWNER TO postgres;

--
-- TOC entry 210 (class 1259 OID 229076)
-- Name: accountable_withdrawal_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW accountable_withdrawal_view AS
 SELECT accountable_withdrawal.accountable_withdrawal_id,
    accountable_withdrawal.accountable_document_id,
    accountable_withdrawal.withdrawal_id
   FROM accountable_withdrawal;


ALTER TABLE accountable_withdrawal_view OWNER TO postgres;

--
-- TOC entry 211 (class 1259 OID 229080)
-- Name: accountables; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE accountables (
    accountable_id integer NOT NULL,
    employee_id integer,
    information character varying(200)
);


ALTER TABLE accountables OWNER TO postgres;

--
-- TOC entry 212 (class 1259 OID 229083)
-- Name: accountables_veiw; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW accountables_veiw AS
 SELECT accountables.accountable_id,
    users.user_id AS employee_id,
    users.user_name AS employee_name,
    users.user_surname AS employee_surname,
    accountables.information,
    users.user_phone AS employee_phone,
    users.user_address AS employee_address,
    ( SELECT roles.role_name
           FROM roles
          WHERE (roles.role_id = users.role_id)) AS role_name
   FROM (accountables
     JOIN users ON ((users.user_id = accountables.employee_id)));


ALTER TABLE accountables_veiw OWNER TO postgres;

--
-- TOC entry 213 (class 1259 OID 229087)
-- Name: accounts; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE accounts (
    account_id integer NOT NULL,
    account_number character varying(20) NOT NULL,
    start_balance numeric(20,3) NOT NULL,
    current_balance numeric(20,3) NOT NULL
);


ALTER TABLE accounts OWNER TO postgres;

--
-- TOC entry 214 (class 1259 OID 229090)
-- Name: accounts_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW accounts_view AS
 SELECT accounts.account_id,
    accounts.account_number,
    accounts.start_balance,
    accounts.current_balance
   FROM accounts;


ALTER TABLE accounts_view OWNER TO postgres;

--
-- TOC entry 215 (class 1259 OID 229094)
-- Name: amortize_group; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE amortize_group (
    amortize_group_id integer NOT NULL,
    group_number integer,
    from_month integer,
    to_month integer
);


ALTER TABLE amortize_group OWNER TO postgres;

--
-- TOC entry 216 (class 1259 OID 229097)
-- Name: amortize_group_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW amortize_group_view AS
 SELECT amortize_group.amortize_group_id,
    amortize_group.group_number,
    amortize_group.from_month,
    amortize_group.to_month
   FROM amortize_group;


ALTER TABLE amortize_group_view OWNER TO postgres;

--
-- TOC entry 217 (class 1259 OID 229101)
-- Name: amortize_type; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE amortize_type (
    amortize_type_id integer NOT NULL,
    amortize_type_name character varying(100),
    amortize_type_code character varying(50)
);


ALTER TABLE amortize_type OWNER TO postgres;

--
-- TOC entry 218 (class 1259 OID 229104)
-- Name: amortize_type_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW amortize_type_view AS
 SELECT amortize_type.amortize_type_id,
    amortize_type.amortize_type_name,
    amortize_type.amortize_type_code
   FROM amortize_type;


ALTER TABLE amortize_type_view OWNER TO postgres;

--
-- TOC entry 219 (class 1259 OID 229108)
-- Name: balance_payment; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE balance_payment (
    balance_payment_id integer NOT NULL,
    balance_id integer NOT NULL,
    payment_id integer NOT NULL
);


ALTER TABLE balance_payment OWNER TO postgres;

--
-- TOC entry 220 (class 1259 OID 229111)
-- Name: balance_payment_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW balance_payment_view AS
 SELECT balance_payment.balance_payment_id,
    balance_payment.balance_id,
    balance_payment.payment_id
   FROM balance_payment;


ALTER TABLE balance_payment_view OWNER TO postgres;

--
-- TOC entry 221 (class 1259 OID 229115)
-- Name: balance_payslip; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE balance_payslip (
    balance_payslip_id integer NOT NULL,
    balance_id integer NOT NULL,
    payslip_id integer NOT NULL
);


ALTER TABLE balance_payslip OWNER TO postgres;

--
-- TOC entry 222 (class 1259 OID 229118)
-- Name: balance_payslip_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW balance_payslip_view AS
 SELECT balance_payslip.balance_payslip_id,
    balance_payslip.balance_id,
    balance_payslip.payslip_id
   FROM balance_payslip;


ALTER TABLE balance_payslip_view OWNER TO postgres;

--
-- TOC entry 223 (class 1259 OID 229122)
-- Name: balance_refund; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE balance_refund (
    balance_refund_id integer NOT NULL,
    balance_id integer NOT NULL,
    refund_id integer NOT NULL
);


ALTER TABLE balance_refund OWNER TO postgres;

--
-- TOC entry 224 (class 1259 OID 229125)
-- Name: balance_refund_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW balance_refund_view AS
 SELECT balance_refund.balance_refund_id,
    balance_refund.balance_id,
    balance_refund.refund_id
   FROM balance_refund;


ALTER TABLE balance_refund_view OWNER TO postgres;

--
-- TOC entry 225 (class 1259 OID 229129)
-- Name: balance_withdrawal; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE balance_withdrawal (
    balance_withdrawal_id integer NOT NULL,
    balance_id integer NOT NULL,
    withdrawal_id integer NOT NULL
);


ALTER TABLE balance_withdrawal OWNER TO postgres;

--
-- TOC entry 226 (class 1259 OID 229132)
-- Name: balance_withdrawal_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW balance_withdrawal_view AS
 SELECT balance_withdrawal.balance_withdrawal_id,
    balance_withdrawal.balance_id,
    balance_withdrawal.withdrawal_id
   FROM balance_withdrawal;


ALTER TABLE balance_withdrawal_view OWNER TO postgres;

--
-- TOC entry 227 (class 1259 OID 229136)
-- Name: balances; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE balances (
    balance_id integer NOT NULL,
    user_id integer NOT NULL,
    subaccount_id integer NOT NULL
);


ALTER TABLE balances OWNER TO postgres;

--
-- TOC entry 228 (class 1259 OID 229139)
-- Name: currencies; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE currencies (
    currency_id integer NOT NULL,
    currency_code integer,
    currency_short_name character varying(3),
    currency_name character varying(20),
    currency_unit integer NOT NULL,
    currency_main_trade boolean
);


ALTER TABLE currencies OWNER TO postgres;

--
-- TOC entry 229 (class 1259 OID 229142)
-- Name: subaccounts; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE subaccounts (
    subaccount_id integer NOT NULL,
    account_id integer NOT NULL,
    subaccount_number character varying(20) NOT NULL,
    start_balance numeric(20,3) NOT NULL,
    current_balance numeric(20,3) NOT NULL,
    currency_id integer NOT NULL,
    status_id integer NOT NULL,
    date_opened date NOT NULL,
    date_closed date,
    details character varying(100)
);


ALTER TABLE subaccounts OWNER TO postgres;

--
-- TOC entry 230 (class 1259 OID 229145)
-- Name: balances_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW balances_view AS
 SELECT balances.balance_id,
    u.user_name,
    u.user_surname,
    s.subaccount_number,
    s.current_balance,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = s.currency_id)) AS currency_name,
    balances.user_id,
    balances.subaccount_id
   FROM ((balances
     JOIN users u ON ((u.user_id = balances.user_id)))
     JOIN subaccounts s ON ((s.subaccount_id = balances.subaccount_id)));


ALTER TABLE balances_view OWNER TO postgres;

--
-- TOC entry 231 (class 1259 OID 229150)
-- Name: borrowers; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE borrowers (
    user_id integer NOT NULL,
    comment character varying(200)
);


ALTER TABLE borrowers OWNER TO postgres;

--
-- TOC entry 232 (class 1259 OID 229153)
-- Name: borrowers_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW borrowers_view AS
 SELECT users.user_id,
    users.user_name,
    users.user_surname,
    borrowers.comment,
    users.user_phone,
    users.user_address,
    ( SELECT roles.role_name
           FROM roles
          WHERE (roles.role_id = users.role_id)) AS role_name,
    users.password,
    users.user_email,
    users.activated,
    users.role_id
   FROM (borrowers
     JOIN users ON ((users.user_id = borrowers.user_id)));


ALTER TABLE borrowers_view OWNER TO postgres;

--
-- TOC entry 233 (class 1259 OID 229158)
-- Name: branch_subaccount; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE branch_subaccount (
    branch_subaccount_id integer NOT NULL,
    branch_id integer,
    subaccount_id integer
);


ALTER TABLE branch_subaccount OWNER TO postgres;

--
-- TOC entry 234 (class 1259 OID 229161)
-- Name: branches; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE branches (
    branch_id integer NOT NULL,
    branch_name character varying(60) NOT NULL,
    branch_address character varying(60) NOT NULL,
    branch_phone character varying(15) NOT NULL,
    commnet character varying(100)
);


ALTER TABLE branches OWNER TO postgres;

--
-- TOC entry 235 (class 1259 OID 229164)
-- Name: branch_subaccount_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW branch_subaccount_view AS
 SELECT branch_subaccount.branch_subaccount_id,
    b.branch_name,
    s.subaccount_number,
    branch_subaccount.branch_id,
    branch_subaccount.subaccount_id
   FROM ((branch_subaccount
     LEFT JOIN branches b ON ((b.branch_id = branch_subaccount.branch_id)))
     LEFT JOIN subaccounts s ON ((s.subaccount_id = branch_subaccount.subaccount_id)));


ALTER TABLE branch_subaccount_view OWNER TO postgres;

--
-- TOC entry 236 (class 1259 OID 229168)
-- Name: branches_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW branches_view AS
 SELECT branches.branch_id,
    branches.branch_name,
    branches.branch_address,
    branches.branch_phone,
    branches.commnet
   FROM branches;


ALTER TABLE branches_view OWNER TO postgres;

--
-- TOC entry 237 (class 1259 OID 229172)
-- Name: cashbox; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE cashbox (
    cashbox_id integer NOT NULL,
    subaccount_id integer NOT NULL,
    information character varying(60),
    cashbox_address character varying(60)
);


ALTER TABLE cashbox OWNER TO postgres;

--
-- TOC entry 238 (class 1259 OID 229175)
-- Name: cashbox_employee; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE cashbox_employee (
    cashbox_employee_id integer NOT NULL,
    cashbox_id integer NOT NULL,
    employee_id integer NOT NULL
);


ALTER TABLE cashbox_employee OWNER TO postgres;

--
-- TOC entry 239 (class 1259 OID 229178)
-- Name: cashbox_employee_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW cashbox_employee_view AS
 SELECT cashbox_employee.cashbox_employee_id,
    ( SELECT subaccounts.subaccount_number
           FROM subaccounts
          WHERE (subaccounts.subaccount_id = c.subaccount_id)) AS subaccount_number,
    c.cashbox_address,
    u.user_name,
    u.user_surname,
    u.user_phone,
    ( SELECT roles.role_name
           FROM roles
          WHERE (roles.role_id = u.role_id)) AS role_name,
    cashbox_employee.cashbox_id,
    cashbox_employee.employee_id
   FROM ((cashbox_employee
     JOIN cashbox c ON ((c.cashbox_id = cashbox_employee.cashbox_id)))
     JOIN users u ON ((u.user_id = cashbox_employee.employee_id)));


ALTER TABLE cashbox_employee_view OWNER TO postgres;

--
-- TOC entry 240 (class 1259 OID 229183)
-- Name: cashbox_transaction; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE cashbox_transaction (
    cashbox_transaction_id integer NOT NULL,
    cashbox_id integer,
    cashier_id integer,
    accountant_id integer,
    owner_id integer,
    payment_id integer,
    withdrawal_id integer
);


ALTER TABLE cashbox_transaction OWNER TO postgres;

--
-- TOC entry 241 (class 1259 OID 229186)
-- Name: cashbox_transaction_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW cashbox_transaction_view AS
 SELECT cashbox_transaction.cashbox_transaction_id,
    cashbox_transaction.cashbox_id,
    cashbox_transaction.cashier_id,
    cashbox_transaction.accountant_id,
    cashbox_transaction.owner_id,
    cashbox_transaction.payment_id,
    cashbox_transaction.withdrawal_id
   FROM cashbox_transaction;


ALTER TABLE cashbox_transaction_view OWNER TO postgres;

--
-- TOC entry 242 (class 1259 OID 229190)
-- Name: cashbox_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW cashbox_view AS
 SELECT cashbox.cashbox_id,
    s.subaccount_number,
    cashbox.information,
    cashbox.cashbox_address,
    cashbox.subaccount_id
   FROM (cashbox
     JOIN subaccounts s ON ((s.subaccount_id = cashbox.subaccount_id)));


ALTER TABLE cashbox_view OWNER TO postgres;

--
-- TOC entry 243 (class 1259 OID 229194)
-- Name: chart_of_accounts; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE chart_of_accounts (
    chart_of_account_id integer NOT NULL,
    number_of_account character varying(5) NOT NULL,
    name_of_account character varying(150) NOT NULL,
    account_type_id integer
);


ALTER TABLE chart_of_accounts OWNER TO postgres;

--
-- TOC entry 244 (class 1259 OID 229197)
-- Name: chart_of_accounts_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW chart_of_accounts_view AS
 SELECT chart_of_accounts.chart_of_account_id,
    chart_of_accounts.number_of_account,
    chart_of_accounts.name_of_account,
    at.account_type_name,
    chart_of_accounts.account_type_id
   FROM (chart_of_accounts
     JOIN account_type at ON ((at.account_type_id = chart_of_accounts.account_type_id)));


ALTER TABLE chart_of_accounts_view OWNER TO postgres;

--
-- TOC entry 245 (class 1259 OID 229201)
-- Name: clients; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE clients (
    user_id integer NOT NULL,
    firm character varying(50) NOT NULL,
    firm_number character varying(10),
    location_id integer NOT NULL
);


ALTER TABLE clients OWNER TO postgres;

--
-- TOC entry 246 (class 1259 OID 229204)
-- Name: locations; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE locations (
    location_id integer NOT NULL,
    country_name character varying(30) NOT NULL,
    country_code character varying(4) NOT NULL,
    region_name character varying(30) NOT NULL,
    city_name character varying(30) NOT NULL
);


ALTER TABLE locations OWNER TO postgres;

--
-- TOC entry 247 (class 1259 OID 229207)
-- Name: clients_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW clients_view AS
 SELECT users.user_id,
    users.user_name,
    users.user_surname,
    users.user_phone,
    ( SELECT locations.country_name
           FROM locations
          WHERE (locations.location_id = clients.location_id)) AS country_name,
    ( SELECT locations.region_name
           FROM locations
          WHERE (locations.location_id = clients.location_id)) AS region_name,
    ( SELECT locations.city_name
           FROM locations
          WHERE (locations.location_id = clients.location_id)) AS city_name,
    users.user_address,
    clients.firm,
    clients.firm_number,
    ( SELECT roles.role_name
           FROM roles
          WHERE (roles.role_id = users.role_id)) AS role_name,
    users.password,
    users.user_email,
    users.activated,
    users.role_id,
    clients.location_id
   FROM (clients
     JOIN users ON ((users.user_id = clients.user_id)));


ALTER TABLE clients_view OWNER TO postgres;

--
-- TOC entry 248 (class 1259 OID 229212)
-- Name: companies; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE companies (
    company_id integer NOT NULL,
    company_name character varying(60) NOT NULL,
    company_address character varying(60) NOT NULL,
    company_phone character varying(15) NOT NULL,
    comment character varying(100)
);


ALTER TABLE companies OWNER TO postgres;

--
-- TOC entry 249 (class 1259 OID 229215)
-- Name: companies_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW companies_view AS
 SELECT companies.company_id,
    companies.company_name,
    companies.company_address,
    companies.company_phone,
    companies.comment
   FROM companies;


ALTER TABLE companies_view OWNER TO postgres;

--
-- TOC entry 250 (class 1259 OID 229219)
-- Name: company_account; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE company_account (
    company_account_id integer NOT NULL,
    company_id integer NOT NULL,
    account_id integer NOT NULL
);


ALTER TABLE company_account OWNER TO postgres;

--
-- TOC entry 251 (class 1259 OID 229222)
-- Name: company_account_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW company_account_view AS
 SELECT company_account.company_account_id,
    c.company_name,
    a.account_number,
    company_account.company_id,
    company_account.account_id
   FROM ((company_account
     JOIN companies c ON ((c.company_id = company_account.company_id)))
     JOIN accounts a ON ((a.account_id = company_account.account_id)));


ALTER TABLE company_account_view OWNER TO postgres;

--
-- TOC entry 252 (class 1259 OID 229226)
-- Name: company_employee; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE company_employee (
    company_employee_id integer NOT NULL,
    company_id integer NOT NULL,
    employee_id integer NOT NULL,
    branch_id integer
);


ALTER TABLE company_employee OWNER TO postgres;

--
-- TOC entry 253 (class 1259 OID 229229)
-- Name: company_employee_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW company_employee_view AS
 SELECT company_employee.company_employee_id,
    c.company_name,
    b.branch_name,
    e.user_name,
    e.user_surname,
    e.user_phone,
    company_employee.company_id,
    company_employee.employee_id,
    company_employee.branch_id
   FROM (((company_employee
     JOIN companies c ON ((c.company_id = company_employee.company_id)))
     JOIN users e ON ((e.user_id = company_employee.employee_id)))
     JOIN branches b ON ((b.branch_id = company_employee.branch_id)));


ALTER TABLE company_employee_view OWNER TO postgres;

--
-- TOC entry 254 (class 1259 OID 229234)
-- Name: consume_other_stocks; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE consume_other_stocks (
    consume_other_stocks_id integer NOT NULL,
    user_id integer,
    consume_other_stocks_date timestamp without time zone NOT NULL,
    execution_date timestamp(0) without time zone,
    employee_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3) NOT NULL,
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE consume_other_stocks OWNER TO postgres;

--
-- TOC entry 255 (class 1259 OID 229237)
-- Name: consume_other_stocks_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE consume_other_stocks_list (
    consume_other_stocks_list_id integer NOT NULL,
    consume_other_stocks_id integer NOT NULL,
    other_stocks_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE consume_other_stocks_list OWNER TO postgres;

--
-- TOC entry 256 (class 1259 OID 229240)
-- Name: measures; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE measures (
    measure_id integer NOT NULL,
    measure_name character varying(15) NOT NULL,
    measure_short_name character varying(4) NOT NULL,
    measure_unit integer
);


ALTER TABLE measures OWNER TO postgres;

--
-- TOC entry 257 (class 1259 OID 229243)
-- Name: other_stocks; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE other_stocks (
    other_stocks_id integer NOT NULL,
    company_id integer NOT NULL,
    other_stocks_name character varying(50) NOT NULL,
    volume numeric(20,5) NOT NULL,
    measure_id integer NOT NULL,
    price numeric(20,5) NOT NULL,
    currency_id integer NOT NULL,
    other_stocks_type_id integer
);


ALTER TABLE other_stocks OWNER TO postgres;

--
-- TOC entry 258 (class 1259 OID 229246)
-- Name: status; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE status (
    status_id integer NOT NULL,
    status_code character varying(4),
    status_name character varying(15),
    comment character varying(100)
);


ALTER TABLE status OWNER TO postgres;

--
-- TOC entry 3698 (class 0 OID 0)
-- Dependencies: 258
-- Name: COLUMN status.status_id; Type: COMMENT; Schema: OrmasSchema; Owner: postgres
--

COMMENT ON COLUMN status.status_id IS '
';


--
-- TOC entry 259 (class 1259 OID 229249)
-- Name: consume_other_stocks_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW consume_other_stocks_list_view AS
 SELECT consume_other_stocks_list.consume_other_stocks_list_id,
    consume_other_stocks_list.consume_other_stocks_id,
    p.other_stocks_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    consume_other_stocks_list.count,
    consume_other_stocks_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = consume_other_stocks_list.currency_id)) AS sum_currency_name,
    s.status_name,
    consume_other_stocks_list.other_stocks_id,
    consume_other_stocks_list.status_id,
    consume_other_stocks_list.currency_id
   FROM ((consume_other_stocks_list
     JOIN other_stocks p ON ((p.other_stocks_id = consume_other_stocks_list.other_stocks_id)))
     JOIN status s ON ((s.status_id = consume_other_stocks_list.status_id)));


ALTER TABLE consume_other_stocks_list_view OWNER TO postgres;

--
-- TOC entry 260 (class 1259 OID 229254)
-- Name: employees; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE employees (
    user_id integer NOT NULL,
    position_id integer NOT NULL,
    birth_date date NOT NULL,
    hire_date date NOT NULL
);


ALTER TABLE employees OWNER TO postgres;

--
-- TOC entry 261 (class 1259 OID 229257)
-- Name: positions; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE positions (
    position_id integer NOT NULL,
    position_name character varying(50) NOT NULL
);


ALTER TABLE positions OWNER TO postgres;

--
-- TOC entry 262 (class 1259 OID 229260)
-- Name: consume_other_stocks_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW consume_other_stocks_view AS
 SELECT consume_other_stocks.consume_other_stocks_id,
    to_char(consume_other_stocks.consume_other_stocks_date, 'dd.MM.yyyy hh24:mm'::text) AS consume_other_stocks_date,
    to_char(consume_other_stocks.execution_date, 'dd.MM.yyyy hh24:mm'::text) AS execution_date,
    s.status_code,
    s.status_name,
    u1.user_name AS employee_name,
    u1.user_surname AS employee_surname,
    u1.user_phone AS employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u1.user_id)))) AS employee_position_name,
    u2.user_name AS stock_employee_name,
    u2.user_surname AS stock_employee_surname,
    u2.user_phone AS stock_employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u2.user_id)))) AS stock_employee_position_name,
    consume_other_stocks.count,
    consume_other_stocks.sum,
    c.currency_short_name AS currency_name,
    consume_other_stocks.employee_id,
    consume_other_stocks.user_id,
    consume_other_stocks.status_id,
    consume_other_stocks.currency_id
   FROM ((((consume_other_stocks
     LEFT JOIN users u1 ON ((u1.user_id = consume_other_stocks.user_id)))
     LEFT JOIN users u2 ON ((u2.user_id = consume_other_stocks.employee_id)))
     LEFT JOIN status s ON ((s.status_id = consume_other_stocks.status_id)))
     LEFT JOIN currencies c ON ((c.currency_id = consume_other_stocks.currency_id)));


ALTER TABLE consume_other_stocks_view OWNER TO postgres;

--
-- TOC entry 263 (class 1259 OID 229265)
-- Name: consume_product_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE consume_product_list (
    consume_product_list_id integer NOT NULL,
    consume_product_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(20,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE consume_product_list OWNER TO postgres;

--
-- TOC entry 264 (class 1259 OID 229268)
-- Name: products; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE products (
    product_id integer NOT NULL,
    company_id integer NOT NULL,
    product_name character varying(50) NOT NULL,
    volume numeric(20,5) NOT NULL,
    measure_id integer NOT NULL,
    price numeric(20,5) NOT NULL,
    product_type_id integer NOT NULL,
    shelf_life integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE products OWNER TO postgres;

--
-- TOC entry 265 (class 1259 OID 229271)
-- Name: consume_product_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW consume_product_list_view AS
 SELECT consume_product_list.consume_product_list_id,
    consume_product_list.consume_product_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    consume_product_list.count,
    consume_product_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = consume_product_list.currency_id)) AS sum_currency_name,
    s.status_name,
    consume_product_list.product_id,
    consume_product_list.status_id,
    consume_product_list.currency_id
   FROM ((consume_product_list
     JOIN products p ON ((p.product_id = consume_product_list.product_id)))
     JOIN status s ON ((s.status_id = consume_product_list.status_id)));


ALTER TABLE consume_product_list_view OWNER TO postgres;

--
-- TOC entry 266 (class 1259 OID 229276)
-- Name: consume_products; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE consume_products (
    consume_product_id integer NOT NULL,
    user_id integer NOT NULL,
    consume_product_date timestamp without time zone NOT NULL,
    execution_date timestamp(0) without time zone,
    employee_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3) NOT NULL,
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE consume_products OWNER TO postgres;

--
-- TOC entry 267 (class 1259 OID 229279)
-- Name: consume_products_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW consume_products_view AS
 SELECT consume_products.consume_product_id,
    to_char(consume_products.consume_product_date, 'dd.MM.yyyy hh24:mi'::text) AS consume_product_date,
    to_char(consume_products.execution_date, 'dd.MM.yyyy hh24:mi'::text) AS execution_date,
    s.status_code,
    s.status_name,
    u1.user_name AS employee_name,
    u1.user_surname AS employee_surname,
    u1.user_phone AS employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u1.user_id)))) AS employee_position_name,
    u2.user_name AS stock_employee_name,
    u2.user_surname AS stock_employee_surname,
    u2.user_phone AS stock_employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u2.user_id)))) AS stock_employee_position_name,
    consume_products.count,
    consume_products.sum,
    c.currency_short_name AS currency_name,
    consume_products.employee_id,
    consume_products.user_id,
    consume_products.status_id,
    consume_products.currency_id
   FROM ((((consume_products
     LEFT JOIN users u1 ON ((u1.user_id = consume_products.user_id)))
     LEFT JOIN users u2 ON ((u2.user_id = consume_products.employee_id)))
     LEFT JOIN status s ON ((s.status_id = consume_products.status_id)))
     LEFT JOIN currencies c ON ((c.currency_id = consume_products.currency_id)));


ALTER TABLE consume_products_view OWNER TO postgres;

--
-- TOC entry 268 (class 1259 OID 229284)
-- Name: consume_raw_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE consume_raw_list (
    consume_raw_list_id integer NOT NULL,
    consume_raw_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE consume_raw_list OWNER TO postgres;

--
-- TOC entry 269 (class 1259 OID 229287)
-- Name: consume_raw_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW consume_raw_list_view AS
 SELECT consume_raw_list.consume_raw_list_id,
    consume_raw_list.consume_raw_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    consume_raw_list.count,
    consume_raw_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = consume_raw_list.currency_id)) AS sum_currency_name,
    s.status_name,
    consume_raw_list.product_id,
    consume_raw_list.status_id,
    consume_raw_list.currency_id
   FROM ((consume_raw_list
     JOIN products p ON ((p.product_id = consume_raw_list.product_id)))
     JOIN status s ON ((s.status_id = consume_raw_list.status_id)));


ALTER TABLE consume_raw_list_view OWNER TO postgres;

--
-- TOC entry 270 (class 1259 OID 229292)
-- Name: consume_raws; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE consume_raws (
    consume_raw_id integer NOT NULL,
    user_id integer NOT NULL,
    consume_raw_date timestamp without time zone NOT NULL,
    execution_date timestamp(0) without time zone,
    employee_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3) NOT NULL,
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE consume_raws OWNER TO postgres;

--
-- TOC entry 271 (class 1259 OID 229295)
-- Name: consume_raws_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW consume_raws_view AS
 SELECT consume_raws.consume_raw_id,
    to_char(consume_raws.consume_raw_date, 'dd.MM.yyyy hh24:mi'::text) AS consume_raw_date,
    to_char(consume_raws.execution_date, 'dd.MM.yyyy hh24:mi'::text) AS execution_date,
    s.status_code,
    s.status_name,
    u1.user_name AS employee_name,
    u1.user_surname AS employee_surname,
    u1.user_phone AS employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u1.user_id)))) AS employee_position_name,
    u2.user_name AS stock_employee_name,
    u2.user_surname AS stock_employee_surname,
    u2.user_phone AS stock_employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u2.user_id)))) AS stock_employee_position_name,
    consume_raws.count,
    consume_raws.sum,
    c.currency_short_name AS currency_name,
    consume_raws.employee_id,
    consume_raws.user_id,
    consume_raws.status_id,
    consume_raws.currency_id
   FROM ((((consume_raws
     LEFT JOIN users u1 ON ((u1.user_id = consume_raws.user_id)))
     LEFT JOIN users u2 ON ((u2.user_id = consume_raws.employee_id)))
     LEFT JOIN status s ON ((s.status_id = consume_raws.status_id)))
     LEFT JOIN currencies c ON ((c.currency_id = consume_raws.currency_id)));


ALTER TABLE consume_raws_view OWNER TO postgres;

--
-- TOC entry 272 (class 1259 OID 229300)
-- Name: creditors; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE creditors (
    creditor_id integer NOT NULL,
    creditor_name character varying(100),
    creditor_address character varying(100),
    crediitor_phone character varying(20),
    company_id integer,
    user_id integer
);


ALTER TABLE creditors OWNER TO postgres;

--
-- TOC entry 273 (class 1259 OID 229303)
-- Name: creditors_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW creditors_view AS
 SELECT creditors.creditor_id,
    creditors.creditor_name,
    creditors.creditor_address,
    creditors.crediitor_phone,
    creditors.company_id,
    creditors.user_id
   FROM creditors;


ALTER TABLE creditors_view OWNER TO postgres;

--
-- TOC entry 274 (class 1259 OID 229307)
-- Name: currencies_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW currencies_view AS
 SELECT currencies.currency_id,
    currencies.currency_code,
    currencies.currency_short_name,
    currencies.currency_name,
    currencies.currency_unit,
    currencies.currency_main_trade
   FROM currencies;


ALTER TABLE currencies_view OWNER TO postgres;

--
-- TOC entry 275 (class 1259 OID 229311)
-- Name: division_account; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE division_account (
    division_account_id integer NOT NULL,
    division_id integer NOT NULL,
    account_id integer NOT NULL,
    account_code character varying(30) NOT NULL
);


ALTER TABLE division_account OWNER TO postgres;

--
-- TOC entry 276 (class 1259 OID 229314)
-- Name: divisions; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE divisions (
    division_id integer NOT NULL,
    division_name character varying(100) NOT NULL,
    division_code character varying(30) NOT NULL
);


ALTER TABLE divisions OWNER TO postgres;

--
-- TOC entry 277 (class 1259 OID 229317)
-- Name: division_account_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW division_account_view AS
 SELECT division_account.division_account_id,
    d.division_name,
    a.account_number,
    ( SELECT chart_of_accounts.name_of_account
           FROM chart_of_accounts
          WHERE ((chart_of_accounts.number_of_account)::text = (a.account_number)::text)) AS account_name,
    division_account.account_code,
    division_account.division_id,
    division_account.account_id
   FROM ((division_account
     JOIN divisions d ON ((d.division_id = division_account.division_id)))
     JOIN accounts a ON ((a.account_id = division_account.account_id)));


ALTER TABLE division_account_view OWNER TO postgres;

--
-- TOC entry 278 (class 1259 OID 229322)
-- Name: division_employee; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE division_employee (
    division_employee_id integer NOT NULL,
    division_id integer NOT NULL,
    employee_id integer,
    is_contract boolean DEFAULT false NOT NULL
);


ALTER TABLE division_employee OWNER TO postgres;

--
-- TOC entry 279 (class 1259 OID 229326)
-- Name: division_employee_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW division_employee_view AS
 SELECT division_employee.division_employee_id,
    division_employee.division_id,
    division_employee.employee_id,
    division_employee.is_contract
   FROM division_employee;


ALTER TABLE division_employee_view OWNER TO postgres;

--
-- TOC entry 280 (class 1259 OID 229330)
-- Name: divisions_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW divisions_view AS
 SELECT divisions.division_id,
    divisions.division_name,
    divisions.division_code
   FROM divisions;


ALTER TABLE divisions_view OWNER TO postgres;

--
-- TOC entry 281 (class 1259 OID 229334)
-- Name: employee_product; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE employee_product (
    employee_product_id integer NOT NULL,
    employee_id integer NOT NULL,
    product_id integer NOT NULL
);


ALTER TABLE employee_product OWNER TO postgres;

--
-- TOC entry 282 (class 1259 OID 229337)
-- Name: employee_product_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW employee_product_view AS
 SELECT employee_product.employee_product_id,
    u.user_name,
    u.user_surname,
    u.user_phone,
    p.product_name,
    p.price,
    employee_product.employee_id,
    employee_product.product_id
   FROM ((employee_product
     JOIN users u ON ((u.user_id = employee_product.employee_id)))
     JOIN products p ON ((p.product_id = employee_product.product_id)));


ALTER TABLE employee_product_view OWNER TO postgres;

--
-- TOC entry 283 (class 1259 OID 229342)
-- Name: employees_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW employees_view AS
 SELECT users.user_id,
    users.user_name,
    users.user_surname,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = employees.position_id)) AS position_name,
    users.user_phone,
    users.user_address,
    to_char((employees.birth_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS birth_date,
    ( SELECT roles.role_name
           FROM roles
          WHERE (roles.role_id = users.role_id)) AS role_name,
    to_char((employees.hire_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS hire_date,
    users.password,
    users.user_email,
    users.activated,
    users.role_id,
    employees.position_id,
    de.division_employee_id,
    de.division_id,
    de.is_contract
   FROM ((employees
     JOIN users ON ((users.user_id = employees.user_id)))
     JOIN division_employee de ON ((de.employee_id = employees.user_id)));


ALTER TABLE employees_view OWNER TO postgres;

--
-- TOC entry 284 (class 1259 OID 229347)
-- Name: entries; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE entries (
    entry_id integer NOT NULL,
    entry_date timestamp without time zone NOT NULL,
    debiting_account_id integer NOT NULL,
    value numeric(20,3) NOT NULL,
    crediting_account_id integer NOT NULL,
    description character varying(200)
);


ALTER TABLE entries OWNER TO postgres;

--
-- TOC entry 285 (class 1259 OID 229350)
-- Name: entry_operation; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE entry_operation (
    entry_operation_id integer NOT NULL,
    entry_id integer NOT NULL,
    operation_id integer NOT NULL
);


ALTER TABLE entry_operation OWNER TO postgres;

--
-- TOC entry 286 (class 1259 OID 229353)
-- Name: entry_subaccount; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE entry_subaccount (
    entry_subaccount_id integer NOT NULL,
    entry_id integer NOT NULL,
    subaccount_id integer NOT NULL
);


ALTER TABLE entry_subaccount OWNER TO postgres;

--
-- TOC entry 287 (class 1259 OID 229356)
-- Name: fixed_assets; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE fixed_assets (
    fixed_assets_id integer NOT NULL,
    fixed_assets_specification_id integer NOT NULL,
    inventory_number character varying(50),
    primary_cost numeric(17,3) NOT NULL,
    stop_cost numeric(17,3),
    service_life integer,
    is_amortize boolean,
    buy_date date,
    start_of_operation_date date,
    end_of_operation_date date,
    status_id integer,
    fixed_assets_details_id integer
);


ALTER TABLE fixed_assets OWNER TO postgres;

--
-- TOC entry 288 (class 1259 OID 229359)
-- Name: fixed_assets_operations; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE fixed_assets_operations (
    fixed_assets_operation_id integer NOT NULL,
    operation_date date,
    operation_name character varying(200),
    operation_value numeric(17,3),
    increment boolean,
    decrement boolean,
    fixed_assets_id integer
);


ALTER TABLE fixed_assets_operations OWNER TO postgres;

--
-- TOC entry 3699 (class 0 OID 0)
-- Dependencies: 288
-- Name: COLUMN fixed_assets_operations.increment; Type: COMMENT; Schema: OrmasSchema; Owner: postgres
--

COMMENT ON COLUMN fixed_assets_operations.increment IS '
';


--
-- TOC entry 289 (class 1259 OID 229362)
-- Name: inventory; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE inventory (
    inventory_id integer NOT NULL,
    inventory_name character varying(200),
    inventory_cost numeric(17,3),
    department_id integer,
    location character varying(200),
    status_id integer,
    start_of_operation_date date,
    end_of_operation_date date,
    inventory_number character varying(50),
    barcode_number character varying(50),
    inventory_subaccount_id integer
);


ALTER TABLE inventory OWNER TO postgres;

--
-- TOC entry 3700 (class 0 OID 0)
-- Dependencies: 289
-- Name: COLUMN inventory.department_id; Type: COMMENT; Schema: OrmasSchema; Owner: postgres
--

COMMENT ON COLUMN inventory.department_id IS '
';


--
-- TOC entry 290 (class 1259 OID 229368)
-- Name: order_raws; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE order_raws (
    order_raw_id integer NOT NULL,
    purveyor_id integer NOT NULL,
    order_raw_date timestamp without time zone NOT NULL,
    execution_date timestamp(0) without time zone,
    employee_id integer,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3) NOT NULL,
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE order_raws OWNER TO postgres;

--
-- TOC entry 291 (class 1259 OID 229371)
-- Name: orders; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE orders (
    order_id integer NOT NULL,
    user_id integer NOT NULL,
    order_date timestamp without time zone NOT NULL,
    execution_date timestamp(0) without time zone,
    employee_id integer,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3) NOT NULL,
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE orders OWNER TO postgres;

--
-- TOC entry 292 (class 1259 OID 229374)
-- Name: payments; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE payments (
    payment_id integer NOT NULL,
    payment_date timestamp without time zone NOT NULL,
    payment_value numeric(20,3) NOT NULL,
    payment_target character varying(100),
    user_id integer,
    currency_id integer NOT NULL,
    status_id integer NOT NULL,
    account_id integer,
    subaccount_id integer,
    who character varying(100),
    cashbox_account_id integer
);


ALTER TABLE payments OWNER TO postgres;

--
-- TOC entry 293 (class 1259 OID 229377)
-- Name: payslips; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE payslips (
    payslip_id integer NOT NULL,
    payslip_date timestamp without time zone,
    payslip_value numeric(20,3) NOT NULL,
    salary_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE payslips OWNER TO postgres;

--
-- TOC entry 294 (class 1259 OID 229380)
-- Name: production_consume_raws; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE production_consume_raws (
    consume_raw_id integer NOT NULL,
    user_id integer,
    consume_raw_date timestamp without time zone NOT NULL,
    execution_date timestamp(0) without time zone,
    employee_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3) NOT NULL,
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE production_consume_raws OWNER TO postgres;

--
-- TOC entry 295 (class 1259 OID 229383)
-- Name: receipt_other_stocks; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE receipt_other_stocks (
    receipt_other_stocks_id integer NOT NULL,
    user_id integer NOT NULL,
    receipt_other_stocks_date timestamp without time zone NOT NULL,
    execution_date timestamp(0) without time zone,
    employee_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3) NOT NULL,
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE receipt_other_stocks OWNER TO postgres;

--
-- TOC entry 296 (class 1259 OID 229386)
-- Name: receipt_products; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE receipt_products (
    receipt_product_id integer NOT NULL,
    user_id integer NOT NULL,
    receipt_product_date timestamp without time zone NOT NULL,
    execution_date timestamp(0) without time zone,
    employee_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3) NOT NULL,
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE receipt_products OWNER TO postgres;

--
-- TOC entry 297 (class 1259 OID 229389)
-- Name: returns; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE returns (
    return_id integer NOT NULL,
    user_id integer,
    return_date timestamp without time zone NOT NULL,
    execution_date timestamp without time zone,
    employee_id integer,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE returns OWNER TO postgres;

--
-- TOC entry 298 (class 1259 OID 229392)
-- Name: spoilage; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE spoilage (
    spoilage_id integer NOT NULL,
    spoilage_date timestamp without time zone NOT NULL,
    employee_id integer,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3) NOT NULL,
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE spoilage OWNER TO postgres;

--
-- TOC entry 299 (class 1259 OID 229395)
-- Name: stock_transfers; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE stock_transfers (
    stock_transfer_id integer NOT NULL,
    user_id integer NOT NULL,
    stock_transfer_date timestamp without time zone NOT NULL,
    execution_date timestamp(0) without time zone,
    employee_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3) NOT NULL,
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE stock_transfers OWNER TO postgres;

--
-- TOC entry 300 (class 1259 OID 229398)
-- Name: withdrawals; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE withdrawals (
    withdrawal_id integer NOT NULL,
    withdrawal_date timestamp without time zone NOT NULL,
    withdrawal_value numeric(20,3) NOT NULL,
    user_id integer,
    subaccount_id integer,
    withdrawal_target character varying(100),
    currency_id integer,
    status_id integer,
    account_id integer,
    who character varying(100),
    cashbox_account_id integer
);


ALTER TABLE withdrawals OWNER TO postgres;

--
-- TOC entry 301 (class 1259 OID 229401)
-- Name: write_off_raws; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE write_off_raws (
    write_off_raw_id integer NOT NULL,
    user_id integer,
    write_off_raw_date timestamp without time zone NOT NULL,
    execution_date timestamp without time zone,
    employee_id integer,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE write_off_raws OWNER TO postgres;

--
-- TOC entry 302 (class 1259 OID 229404)
-- Name: write_offs; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE write_offs (
    write_off_id integer NOT NULL,
    user_id integer,
    write_off_date timestamp without time zone NOT NULL,
    execution_date timestamp without time zone,
    employee_id integer,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE write_offs OWNER TO postgres;

--
-- TOC entry 303 (class 1259 OID 229407)
-- Name: entries_all_joins_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW entries_all_joins_view AS
 SELECT entries.entry_id,
    to_char(entries.entry_date, 'dd.MM.yyyy'::text) AS entry_date,
    da.account_number AS debiting_account_number,
    entries.value,
    ca.account_number AS crediting_account_number,
    eo.operation_id,
    es.subaccount_id,
    entries.debiting_account_id,
    entries.crediting_account_id,
    entries.description,
    cp.consume_product_id,
    cr.consume_raw_id,
    fa.fixed_assets_id,
    fao.fixed_assets_operation_id,
    i.inventory_id,
    o.order_id,
    ord.order_raw_id,
    p.payment_id,
    ps.payslip_id,
    pcr.consume_raw_id AS production_consume_raw_id,
    rp.receipt_product_id,
    r.return_id,
    s.spoilage_id,
    st.stock_transfer_id,
    w.withdrawal_id,
    wo.write_off_id,
    wor.write_off_raw_id,
    pro.product_id,
    os.other_stocks_id,
    ros.receipt_other_stocks_id,
    cos.consume_other_stocks_id,
    ad.accountable_document_id
   FROM ((((((((((((((((((((((((((entries
     LEFT JOIN accounts da ON ((da.account_id = entries.debiting_account_id)))
     LEFT JOIN entry_operation eo ON ((eo.entry_id = entries.entry_id)))
     LEFT JOIN entry_subaccount es ON ((es.entry_id = entries.entry_id)))
     LEFT JOIN accounts ca ON ((ca.account_id = entries.crediting_account_id)))
     LEFT JOIN consume_products cp ON ((cp.consume_product_id = eo.operation_id)))
     LEFT JOIN consume_raws cr ON ((cr.consume_raw_id = eo.operation_id)))
     LEFT JOIN fixed_assets fa ON ((fa.fixed_assets_id = eo.operation_id)))
     LEFT JOIN fixed_assets_operations fao ON ((fao.fixed_assets_operation_id = eo.operation_id)))
     LEFT JOIN inventory i ON ((i.inventory_id = eo.operation_id)))
     LEFT JOIN orders o ON ((o.order_id = eo.operation_id)))
     LEFT JOIN order_raws ord ON ((ord.order_raw_id = eo.operation_id)))
     LEFT JOIN payments p ON ((p.payment_id = eo.operation_id)))
     LEFT JOIN payslips ps ON ((ps.payslip_id = eo.operation_id)))
     LEFT JOIN production_consume_raws pcr ON ((pcr.consume_raw_id = eo.operation_id)))
     LEFT JOIN receipt_products rp ON ((rp.receipt_product_id = eo.operation_id)))
     LEFT JOIN returns r ON ((r.return_id = eo.operation_id)))
     LEFT JOIN spoilage s ON ((s.spoilage_id = eo.operation_id)))
     LEFT JOIN stock_transfers st ON ((st.stock_transfer_id = eo.operation_id)))
     LEFT JOIN withdrawals w ON ((w.withdrawal_id = eo.operation_id)))
     LEFT JOIN write_offs wo ON ((wo.write_off_id = eo.operation_id)))
     LEFT JOIN write_off_raws wor ON ((wor.write_off_raw_id = eo.operation_id)))
     LEFT JOIN products pro ON ((pro.product_id = eo.operation_id)))
     LEFT JOIN other_stocks os ON ((os.other_stocks_id = eo.operation_id)))
     LEFT JOIN receipt_other_stocks ros ON ((ros.receipt_other_stocks_id = eo.operation_id)))
     LEFT JOIN consume_other_stocks cos ON ((cos.consume_other_stocks_id = eo.operation_id)))
     LEFT JOIN accountable_documents ad ON ((ad.accountable_document_id = eo.operation_id)))
  ORDER BY entries.entry_id;


ALTER TABLE entries_all_joins_view OWNER TO postgres;

--
-- TOC entry 304 (class 1259 OID 229412)
-- Name: entries_full_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW entries_full_view AS
 SELECT DISTINCT ON (entries.entry_id) entries.entry_id,
    to_char(entries.entry_date, 'dd.MM.yyyy'::text) AS entry_date,
    da.account_number AS debiting_account_number,
    entries.value,
    ca.account_number AS crediting_account_number,
    eo.operation_id,
    es.subaccount_id,
    entries.debiting_account_id,
    entries.crediting_account_id,
    entries.description
   FROM ((((entries
     LEFT JOIN accounts da ON ((da.account_id = entries.debiting_account_id)))
     LEFT JOIN entry_operation eo ON ((eo.entry_id = entries.entry_id)))
     LEFT JOIN entry_subaccount es ON ((es.entry_id = entries.entry_id)))
     LEFT JOIN accounts ca ON ((ca.account_id = entries.crediting_account_id)))
  ORDER BY entries.entry_id;


ALTER TABLE entries_full_view OWNER TO postgres;

--
-- TOC entry 305 (class 1259 OID 229417)
-- Name: entries_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW entries_view AS
 SELECT entries.entry_id,
    to_char(entries.entry_date, 'dd.MM.yyyy'::text) AS entry_date,
    da.account_number AS debiting_account_number,
    entries.value,
    ca.account_number AS crediting_account_number,
    entries.debiting_account_id,
    entries.crediting_account_id,
    entries.description
   FROM ((entries
     JOIN accounts da ON ((da.account_id = entries.debiting_account_id)))
     JOIN accounts ca ON ((ca.account_id = entries.crediting_account_id)));


ALTER TABLE entries_view OWNER TO postgres;

--
-- TOC entry 306 (class 1259 OID 229421)
-- Name: entry_operation_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW entry_operation_view AS
 SELECT entry_operation.entry_operation_id,
    entry_operation.entry_id,
    entry_operation.operation_id
   FROM entry_operation;


ALTER TABLE entry_operation_view OWNER TO postgres;

--
-- TOC entry 307 (class 1259 OID 229425)
-- Name: entry_routing; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE entry_routing (
    entry_routing_id integer NOT NULL,
    operation_name character varying(200) NOT NULL,
    debit integer NOT NULL,
    credit integer NOT NULL
);


ALTER TABLE entry_routing OWNER TO postgres;

--
-- TOC entry 308 (class 1259 OID 229428)
-- Name: entry_routing_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW entry_routing_view AS
 SELECT entry_routing.entry_routing_id,
    entry_routing.operation_name,
    entry_routing.debit,
    entry_routing.credit
   FROM entry_routing;


ALTER TABLE entry_routing_view OWNER TO postgres;

--
-- TOC entry 309 (class 1259 OID 229432)
-- Name: entry_subaccount_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW entry_subaccount_view AS
 SELECT entry_subaccount.entry_subaccount_id,
    entry_subaccount.entry_id,
    entry_subaccount.subaccount_id
   FROM entry_subaccount;


ALTER TABLE entry_subaccount_view OWNER TO postgres;

--
-- TOC entry 310 (class 1259 OID 229436)
-- Name: expense_document; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE expense_document (
    expense_document_id integer NOT NULL,
    name character varying(300),
    count numeric(20,5),
    sum numeric(20,3),
    measure_id integer,
    currency_id integer
);


ALTER TABLE expense_document OWNER TO postgres;

--
-- TOC entry 311 (class 1259 OID 229439)
-- Name: expense_document_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW expense_document_view AS
 SELECT expense_document.expense_document_id,
    expense_document.name,
    expense_document.count,
    expense_document.sum,
    expense_document.measure_id,
    expense_document.currency_id
   FROM expense_document;


ALTER TABLE expense_document_view OWNER TO postgres;

--
-- TOC entry 312 (class 1259 OID 229443)
-- Name: financial_report; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE financial_report (
    financial_report_id integer NOT NULL,
    acc_44010 numeric(20,3),
    acc_55010 numeric(20,3),
    acc_552 numeric(20,3),
    acc_55270 numeric(20,3),
    acc_553 numeric(20,3),
    acc_55321 numeric(20,3),
    acc_44020_90 numeric(20,3),
    acc_66010_66110 numeric(20,3),
    acc_66020_66120 numeric(20,3),
    acc_66040_66140 numeric(20,3),
    acc_66050_66150 numeric(20,3),
    acc_66060_66160 numeric(20,3),
    acc_66130 numeric(20,3),
    acc_66070_66170 numeric(20,3),
    tax numeric(20,3),
    from_date date,
    till_date date
);


ALTER TABLE financial_report OWNER TO postgres;

--
-- TOC entry 313 (class 1259 OID 229446)
-- Name: financial_report_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW financial_report_view AS
 SELECT financial_report.financial_report_id,
    financial_report.acc_44010,
    financial_report.acc_55010,
    financial_report.acc_552,
    financial_report.acc_55270,
    financial_report.acc_553,
    financial_report.acc_55321,
    financial_report.acc_44020_90,
    financial_report.acc_66010_66110,
    financial_report.acc_66020_66120,
    financial_report.acc_66040_66140,
    financial_report.acc_66050_66150,
    financial_report.acc_66060_66160,
    financial_report.acc_66130,
    financial_report.acc_66070_66170,
    financial_report.tax,
    financial_report.from_date,
    financial_report.till_date
   FROM financial_report;


ALTER TABLE financial_report_view OWNER TO postgres;

--
-- TOC entry 314 (class 1259 OID 229450)
-- Name: fixed_assets_details; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE fixed_assets_details (
    fixed_assets_details_id integer NOT NULL,
    amortize_group_id integer,
    amortize_type_id integer,
    department_id integer,
    fixed_assets_location character varying(200),
    primary_cost_account_id integer,
    amortize_account_id integer,
    barcode_number character varying(50),
    amortize_value numeric(20,3)
);


ALTER TABLE fixed_assets_details OWNER TO postgres;

--
-- TOC entry 315 (class 1259 OID 229453)
-- Name: fixed_assets_details_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW fixed_assets_details_view AS
 SELECT fixed_assets_details.fixed_assets_details_id,
    ag.group_number,
    at.amortize_type_name,
    at.amortize_type_code,
    fixed_assets_details.amortize_value,
    d.division_name,
    ps.current_balance AS primary_cost_value,
    ams.current_balance AS amortize_acc_value,
    fixed_assets_details.barcode_number,
    fixed_assets_details.fixed_assets_location,
    fixed_assets_details.primary_cost_account_id,
    fixed_assets_details.amortize_account_id,
    fixed_assets_details.amortize_group_id,
    fixed_assets_details.amortize_type_id,
    fixed_assets_details.department_id
   FROM (((((fixed_assets_details
     LEFT JOIN amortize_group ag ON ((ag.amortize_group_id = fixed_assets_details.amortize_group_id)))
     LEFT JOIN amortize_type at ON ((at.amortize_type_id = fixed_assets_details.amortize_type_id)))
     LEFT JOIN divisions d ON ((d.division_id = fixed_assets_details.department_id)))
     LEFT JOIN subaccounts ps ON ((ps.subaccount_id = fixed_assets_details.primary_cost_account_id)))
     LEFT JOIN subaccounts ams ON ((ams.subaccount_id = fixed_assets_details.amortize_account_id)));


ALTER TABLE fixed_assets_details_view OWNER TO postgres;

--
-- TOC entry 316 (class 1259 OID 229458)
-- Name: fixed_assets_operations_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW fixed_assets_operations_view AS
 SELECT fixed_assets_operations.fixed_assets_operation_id,
    to_char((fixed_assets_operations.operation_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS operation_date,
    fixed_assets_operations.operation_name,
    fixed_assets_operations.operation_value,
    fixed_assets_operations.increment,
    fixed_assets_operations.decrement,
    fixed_assets_operations.fixed_assets_id
   FROM fixed_assets_operations;


ALTER TABLE fixed_assets_operations_view OWNER TO postgres;

--
-- TOC entry 317 (class 1259 OID 229462)
-- Name: fixed_assets_specification; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE fixed_assets_specification (
    fixed_assets_specification_id integer NOT NULL,
    fixed_assets_name character varying(200),
    factory_number character varying(30),
    developer character varying(100),
    document character varying(200),
    object_characters character varying(400),
    condition character varying(100),
    date_of_construction date
);


ALTER TABLE fixed_assets_specification OWNER TO postgres;

--
-- TOC entry 318 (class 1259 OID 229468)
-- Name: fixed_assets_specification_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW fixed_assets_specification_view AS
 SELECT fixed_assets_specification.fixed_assets_specification_id,
    fixed_assets_specification.fixed_assets_name,
    fixed_assets_specification.factory_number,
    fixed_assets_specification.developer,
    fixed_assets_specification.document,
    fixed_assets_specification.object_characters,
    fixed_assets_specification.condition,
    to_char((fixed_assets_specification.date_of_construction)::timestamp with time zone, 'dd.MM.yyyy'::text) AS date_of_construction
   FROM fixed_assets_specification;


ALTER TABLE fixed_assets_specification_view OWNER TO postgres;

--
-- TOC entry 319 (class 1259 OID 229472)
-- Name: posting_fixed_assets; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE posting_fixed_assets (
    posting_fixed_assets_id integer NOT NULL,
    user_id integer,
    subaccount_id integer,
    account_id integer,
    fixed_assets_id integer,
    inventory_id integer
);


ALTER TABLE posting_fixed_assets OWNER TO postgres;

--
-- TOC entry 320 (class 1259 OID 229475)
-- Name: fixed_assets_union_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW fixed_assets_union_view AS
 SELECT fixed_assets.fixed_assets_id,
    fas.fixed_assets_name,
    ( SELECT divisions.division_name
           FROM divisions
          WHERE (divisions.division_id = fad.department_id)) AS division_name,
    fixed_assets.primary_cost,
    fixed_assets.stop_cost,
    ( SELECT subaccounts.current_balance
           FROM subaccounts
          WHERE (subaccounts.subaccount_id = fad.amortize_account_id)) AS amortize_sum,
    fixed_assets.inventory_number,
    fad.amortize_value,
    fixed_assets.service_life,
    fixed_assets.is_amortize,
    s.status_name,
    to_char((fixed_assets.buy_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS buy_date,
    to_char((fixed_assets.start_of_operation_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS start_of_operation_date,
    to_char((fixed_assets.end_of_operation_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS end_of_operation_date,
    fad.fixed_assets_location,
    fad.barcode_number,
    fas.factory_number,
    fas.developer,
    fas.document,
    fas.object_characters,
    fas.condition,
    to_char((fas.date_of_construction)::timestamp with time zone, 'dd.MM.yyyy'::text) AS date_of_construction,
    fas.fixed_assets_specification_id,
    fixed_assets.status_id,
    fad.fixed_assets_details_id,
    fad.amortize_group_id,
    fad.amortize_type_id,
    fad.department_id,
    fad.primary_cost_account_id,
    fad.amortize_account_id,
    pfa.posting_fixed_assets_id,
    pfa.user_id,
    pfa.subaccount_id,
    pfa.account_id
   FROM ((((fixed_assets
     LEFT JOIN fixed_assets_specification fas ON ((fas.fixed_assets_specification_id = fixed_assets.fixed_assets_specification_id)))
     LEFT JOIN fixed_assets_details fad ON ((fad.fixed_assets_details_id = fixed_assets.fixed_assets_details_id)))
     LEFT JOIN posting_fixed_assets pfa ON ((pfa.fixed_assets_id = fixed_assets.fixed_assets_id)))
     LEFT JOIN status s ON ((s.status_id = fixed_assets.status_id)));


ALTER TABLE fixed_assets_union_view OWNER TO postgres;

--
-- TOC entry 321 (class 1259 OID 229480)
-- Name: fixed_assets_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW fixed_assets_view AS
 SELECT fixed_assets.fixed_assets_id,
    fs.fixed_assets_name,
    fixed_assets.inventory_number,
    fixed_assets.primary_cost,
    fixed_assets.stop_cost,
    ( SELECT subaccounts.current_balance
           FROM subaccounts
          WHERE (subaccounts.subaccount_id = fd.primary_cost_account_id)) AS primary_cost_value,
    ( SELECT subaccounts.current_balance
           FROM subaccounts
          WHERE (subaccounts.subaccount_id = fd.amortize_account_id)) AS amortize_value,
    ( SELECT divisions.division_name
           FROM divisions
          WHERE (divisions.division_id = fd.department_id)) AS division_name,
    s.status_name,
    fixed_assets.service_life,
    fixed_assets.is_amortize,
    to_char((fixed_assets.buy_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS buy_date,
    to_char((fixed_assets.start_of_operation_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS start_of_operation_date,
    to_char((fixed_assets.end_of_operation_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS end_of_operation_date,
    fixed_assets.fixed_assets_specification_id,
    fixed_assets.status_id,
    fixed_assets.fixed_assets_details_id,
    ( SELECT subaccounts.account_id
           FROM subaccounts
          WHERE (subaccounts.subaccount_id = fd.primary_cost_account_id)) AS primary_parent_account_id,
    ( SELECT subaccounts.account_id
           FROM subaccounts
          WHERE (subaccounts.subaccount_id = fd.amortize_account_id)) AS amortize_parent_account_id
   FROM (((fixed_assets
     LEFT JOIN fixed_assets_specification fs ON ((fs.fixed_assets_specification_id = fixed_assets.fixed_assets_specification_id)))
     LEFT JOIN fixed_assets_details fd ON ((fd.fixed_assets_details_id = fixed_assets.fixed_assets_details_id)))
     LEFT JOIN status s ON ((s.status_id = fixed_assets.status_id)));


ALTER TABLE fixed_assets_view OWNER TO postgres;

--
-- TOC entry 322 (class 1259 OID 229485)
-- Name: groups; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE groups (
    group_id integer NOT NULL,
    group_name character varying(80),
    definition character varying(80)
);


ALTER TABLE groups OWNER TO postgres;

--
-- TOC entry 323 (class 1259 OID 229488)
-- Name: group_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW group_view AS
 SELECT groups.group_id,
    groups.group_name,
    groups.definition
   FROM groups;


ALTER TABLE group_view OWNER TO postgres;

--
-- TOC entry 324 (class 1259 OID 229492)
-- Name: id_seq; Type: SEQUENCE; Schema: OrmasSchema; Owner: postgres
--

CREATE SEQUENCE id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    MAXVALUE 9999999999
    CACHE 1;


ALTER TABLE id_seq OWNER TO postgres;

--
-- TOC entry 325 (class 1259 OID 229494)
-- Name: inv_seq; Type: SEQUENCE; Schema: OrmasSchema; Owner: postgres
--

CREATE SEQUENCE inv_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    MAXVALUE 999999999
    CACHE 1;


ALTER TABLE inv_seq OWNER TO postgres;

--
-- TOC entry 326 (class 1259 OID 229496)
-- Name: inventorization_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE inventorization_list (
    inventorization_list_id integer NOT NULL,
    inventorization_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE inventorization_list OWNER TO postgres;

--
-- TOC entry 327 (class 1259 OID 229499)
-- Name: inventorization_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW inventorization_list_view AS
 SELECT inventorization_list.inventorization_list_id,
    inventorization_list.inventorization_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    inventorization_list.count,
    inventorization_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = inventorization_list.currency_id)) AS sum_currency_name,
    s.status_name,
    inventorization_list.product_id,
    inventorization_list.status_id,
    inventorization_list.currency_id
   FROM ((inventorization_list
     JOIN products p ON ((p.product_id = inventorization_list.product_id)))
     JOIN status s ON ((s.status_id = inventorization_list.status_id)));


ALTER TABLE inventorization_list_view OWNER TO postgres;

--
-- TOC entry 328 (class 1259 OID 229504)
-- Name: inventorizations; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE inventorizations (
    inventorization_id integer NOT NULL,
    user_id integer NOT NULL,
    inventorization_date timestamp without time zone NOT NULL,
    execution_date timestamp(0) without time zone,
    employee_id integer,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3) NOT NULL,
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE inventorizations OWNER TO postgres;

--
-- TOC entry 329 (class 1259 OID 229507)
-- Name: inventorizations_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW inventorizations_view AS
 SELECT inventorizations.inventorization_id,
    to_char(inventorizations.inventorization_date, 'dd.MM.yyyy hh24:mi'::text) AS inventorization_date,
    to_char(inventorizations.execution_date, 'dd.MM.yyyy hh24:mi'::text) AS execution_date,
    s.status_code,
    s.status_name,
    u1.user_name AS employee_name,
    u1.user_surname AS employee_surname,
    u1.user_phone AS employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u1.user_id)))) AS employee_position_name,
    u2.user_name AS stock_employee_name,
    u2.user_surname AS stock_employee_surname,
    u2.user_phone AS stock_employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u2.user_id)))) AS stock_employee_position_name,
    inventorizations.count,
    inventorizations.sum,
    c.currency_short_name AS currency_name,
    inventorizations.employee_id,
    inventorizations.user_id,
    inventorizations.status_id,
    inventorizations.currency_id
   FROM ((((inventorizations
     LEFT JOIN users u1 ON ((u1.user_id = inventorizations.user_id)))
     LEFT JOIN users u2 ON ((u2.user_id = inventorizations.employee_id)))
     LEFT JOIN status s ON ((s.status_id = inventorizations.status_id)))
     LEFT JOIN currencies c ON ((c.currency_id = inventorizations.currency_id)));


ALTER TABLE inventorizations_view OWNER TO postgres;

--
-- TOC entry 330 (class 1259 OID 229512)
-- Name: inventory_history; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE inventory_history (
    inventory_history_id integer NOT NULL,
    inventory_id integer,
    comment character varying(300),
    change_date date
);


ALTER TABLE inventory_history OWNER TO postgres;

--
-- TOC entry 331 (class 1259 OID 229515)
-- Name: inventory_history_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW inventory_history_view AS
 SELECT inventory_history.inventory_history_id,
    inventory_history.inventory_id,
    inventory_history.comment,
    to_char((inventory_history.change_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS change_date
   FROM inventory_history;


ALTER TABLE inventory_history_view OWNER TO postgres;

--
-- TOC entry 332 (class 1259 OID 229519)
-- Name: inventory_union_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW inventory_union_view AS
 SELECT inventory.inventory_id,
    inventory.inventory_name,
    inventory.inventory_cost,
    inventory.inventory_number,
    inventory.barcode_number,
    divisions.division_name,
    s.status_name,
    inventory.location,
    inventory.start_of_operation_date,
    inventory.end_of_operation_date,
    inventory.status_id,
    inventory.department_id,
    inventory.inventory_subaccount_id,
    pfa.posting_fixed_assets_id,
    pfa.user_id,
    pfa.subaccount_id,
    pfa.account_id
   FROM ((((inventory
     LEFT JOIN status s ON ((s.status_id = inventory.status_id)))
     LEFT JOIN divisions ON ((divisions.division_id = inventory.department_id)))
     LEFT JOIN posting_fixed_assets pfa ON ((pfa.inventory_id = inventory.inventory_id)))
     LEFT JOIN subaccounts ON ((subaccounts.subaccount_id = inventory.inventory_subaccount_id)));


ALTER TABLE inventory_union_view OWNER TO postgres;

--
-- TOC entry 333 (class 1259 OID 229524)
-- Name: inventory_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW inventory_view AS
 SELECT inventory.inventory_id,
    inventory.inventory_name,
    inventory.inventory_cost,
    inventory.inventory_number,
    inventory.barcode_number,
    divisions.division_name,
    s.status_name,
    inventory.location,
    inventory.start_of_operation_date,
    inventory.end_of_operation_date,
    inventory.status_id,
    inventory.department_id,
    inventory.inventory_subaccount_id
   FROM (((inventory
     LEFT JOIN status s ON ((s.status_id = inventory.status_id)))
     LEFT JOIN divisions ON ((divisions.division_id = inventory.department_id)))
     LEFT JOIN subaccounts ON ((subaccounts.subaccount_id = inventory.inventory_subaccount_id)));


ALTER TABLE inventory_view OWNER TO postgres;

--
-- TOC entry 334 (class 1259 OID 229529)
-- Name: jobprice; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE jobprice (
    jobprice_id integer NOT NULL,
    product_id integer NOT NULL,
    value numeric(20,3) NOT NULL,
    currency_id integer NOT NULL,
    volume numeric(20,3) NOT NULL,
    measure_id integer NOT NULL,
    position_id integer NOT NULL
);


ALTER TABLE jobprice OWNER TO postgres;

--
-- TOC entry 335 (class 1259 OID 229532)
-- Name: jobprice_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW jobprice_view AS
 SELECT jobprice.jobprice_id,
    p.product_name,
    jobprice.value,
    c.currency_short_name AS currency_name,
    jobprice.volume,
    m.measure_name,
    pos.position_name,
    jobprice.product_id,
    jobprice.currency_id,
    jobprice.measure_id,
    jobprice.position_id
   FROM ((((jobprice
     JOIN products p ON ((p.product_id = jobprice.product_id)))
     JOIN currencies c ON ((c.currency_id = jobprice.currency_id)))
     JOIN measures m ON ((m.measure_id = jobprice.measure_id)))
     JOIN positions pos ON ((pos.position_id = jobprice.position_id)));


ALTER TABLE jobprice_view OWNER TO postgres;

--
-- TOC entry 336 (class 1259 OID 229537)
-- Name: jobsheet; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE jobsheet (
    jobsheet_id integer NOT NULL,
    jobsheet_date date NOT NULL,
    count numeric(20,3) NOT NULL,
    product_id integer NOT NULL,
    employee_id integer NOT NULL
);


ALTER TABLE jobsheet OWNER TO postgres;

--
-- TOC entry 337 (class 1259 OID 229540)
-- Name: jobsheet_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW jobsheet_view AS
 SELECT jobsheet.jobsheet_id,
    to_char((jobsheet.jobsheet_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS jobsheet_date,
    e.user_name,
    e.user_surname,
    e.user_phone,
    p.product_name,
    jobsheet.count,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    jobsheet.product_id,
    jobsheet.employee_id
   FROM ((jobsheet
     JOIN products p ON ((p.product_id = jobsheet.product_id)))
     JOIN users e ON ((e.user_id = jobsheet.employee_id)));


ALTER TABLE jobsheet_view OWNER TO postgres;

--
-- TOC entry 338 (class 1259 OID 229545)
-- Name: locations_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW locations_view AS
 SELECT locations.location_id,
    locations.country_name,
    locations.country_code,
    locations.region_name,
    locations.city_name
   FROM locations;


ALTER TABLE locations_view OWNER TO postgres;

--
-- TOC entry 339 (class 1259 OID 229549)
-- Name: low_value_stock; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE low_value_stock (
    low_value_stock_id integer NOT NULL,
    other_stocks_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL,
    warehouse_id integer
);


ALTER TABLE low_value_stock OWNER TO postgres;

--
-- TOC entry 340 (class 1259 OID 229552)
-- Name: low_value_stock_change_log; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE low_value_stock_change_log (
    low_value_stock_change_log_id integer NOT NULL,
    low_value_stock_id integer,
    other_stocks_id integer,
    count numeric(15,5),
    sum numeric(20,3),
    status_id integer,
    currency_id integer,
    warehouse_id integer,
    log_date timestamp without time zone,
    user_id integer,
    operation_id integer
);


ALTER TABLE low_value_stock_change_log OWNER TO postgres;

--
-- TOC entry 341 (class 1259 OID 229555)
-- Name: low_value_stock_change_log_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW low_value_stock_change_log_view AS
 SELECT low_value_stock_change_log.low_value_stock_change_log_id,
    low_value_stock_change_log.low_value_stock_id,
    low_value_stock_change_log.other_stocks_id,
    low_value_stock_change_log.count,
    low_value_stock_change_log.sum,
    low_value_stock_change_log.status_id,
    low_value_stock_change_log.currency_id,
    low_value_stock_change_log.warehouse_id,
    to_char(low_value_stock_change_log.log_date, 'dd.MM.yyyy hh24:mi'::text) AS log_date,
    low_value_stock_change_log.user_id,
    low_value_stock_change_log.operation_id
   FROM low_value_stock_change_log;


ALTER TABLE low_value_stock_change_log_view OWNER TO postgres;

--
-- TOC entry 342 (class 1259 OID 229559)
-- Name: low_value_stock_history; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE low_value_stock_history (
    low_value_stock_id integer NOT NULL,
    other_stocks_id integer,
    count numeric(15,5),
    sum numeric(20,3),
    status_id integer,
    currency_id integer,
    warehouse_id integer,
    history_date timestamp without time zone
);


ALTER TABLE low_value_stock_history OWNER TO postgres;

--
-- TOC entry 343 (class 1259 OID 229562)
-- Name: warehouse; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE warehouse (
    warehouse_id integer NOT NULL,
    warehouse_name character varying(60) NOT NULL,
    warehouse_address character varying(60) NOT NULL,
    warehouse_phone character varying(15),
    warehouse_type_id integer NOT NULL,
    subaccount_id integer NOT NULL
);


ALTER TABLE warehouse OWNER TO postgres;

--
-- TOC entry 344 (class 1259 OID 229565)
-- Name: low_value_stock_history_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW low_value_stock_history_view AS
 SELECT low_value_stock_history.low_value_stock_id,
    p.other_stocks_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    low_value_stock_history.count,
    low_value_stock_history.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = low_value_stock_history.currency_id)) AS sum_currency_name,
    w.warehouse_name,
    ( SELECT subaccounts.subaccount_number
           FROM subaccounts
          WHERE (subaccounts.subaccount_id = w.subaccount_id)) AS subaccount_number,
    s.status_name,
    low_value_stock_history.other_stocks_id,
    low_value_stock_history.status_id,
    low_value_stock_history.currency_id,
    low_value_stock_history.warehouse_id,
    low_value_stock_history.history_date
   FROM (((low_value_stock_history
     LEFT JOIN other_stocks p ON ((p.other_stocks_id = low_value_stock_history.other_stocks_id)))
     LEFT JOIN status s ON ((s.status_id = low_value_stock_history.status_id)))
     LEFT JOIN warehouse w ON ((w.warehouse_id = low_value_stock_history.warehouse_id)));


ALTER TABLE low_value_stock_history_view OWNER TO postgres;

--
-- TOC entry 345 (class 1259 OID 229570)
-- Name: low_value_stock_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW low_value_stock_view AS
 SELECT low_value_stock.low_value_stock_id,
    p.other_stocks_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    low_value_stock.count,
    low_value_stock.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = low_value_stock.currency_id)) AS sum_currency_name,
    w.warehouse_name,
    ( SELECT subaccounts.subaccount_number
           FROM subaccounts
          WHERE (subaccounts.subaccount_id = w.subaccount_id)) AS subaccount_number,
    s.status_name,
    low_value_stock.other_stocks_id,
    low_value_stock.status_id,
    low_value_stock.currency_id,
    low_value_stock.warehouse_id
   FROM (((low_value_stock
     JOIN other_stocks p ON ((p.other_stocks_id = low_value_stock.other_stocks_id)))
     JOIN status s ON ((s.status_id = low_value_stock.status_id)))
     JOIN warehouse w ON ((w.warehouse_id = low_value_stock.warehouse_id)))
  ORDER BY p.other_stocks_name;


ALTER TABLE low_value_stock_view OWNER TO postgres;

--
-- TOC entry 346 (class 1259 OID 229575)
-- Name: measures_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW measures_view AS
 SELECT measures.measure_id,
    measures.measure_name,
    measures.measure_short_name,
    measures.measure_unit
   FROM measures;


ALTER TABLE measures_view OWNER TO postgres;

--
-- TOC entry 347 (class 1259 OID 229579)
-- Name: net_cost; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE net_cost (
    net_cost_id integer NOT NULL,
    net_cost_date timestamp without time zone NOT NULL,
    net_cost_value numeric(20,3) NOT NULL,
    currency_id integer NOT NULL,
    product_id integer NOT NULL,
    is_outdated boolean
);


ALTER TABLE net_cost OWNER TO postgres;

--
-- TOC entry 348 (class 1259 OID 229582)
-- Name: net_cost_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW net_cost_view AS
 SELECT net_cost.net_cost_id,
    to_char(net_cost.net_cost_date, 'dd.MM.yyyy hh24:mi'::text) AS net_cost_date,
    p.product_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    net_cost.net_cost_value,
    c.currency_short_name AS currency_name,
    net_cost.currency_id,
    net_cost.product_id,
    net_cost.is_outdated
   FROM ((net_cost
     JOIN products p ON ((p.product_id = net_cost.product_id)))
     JOIN currencies c ON ((c.currency_id = net_cost.currency_id)));


ALTER TABLE net_cost_view OWNER TO postgres;

--
-- TOC entry 349 (class 1259 OID 229587)
-- Name: order_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE order_list (
    order_list_id integer NOT NULL,
    order_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE order_list OWNER TO postgres;

--
-- TOC entry 350 (class 1259 OID 229590)
-- Name: order_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW order_list_view AS
 SELECT order_list.order_list_id,
    order_list.order_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    order_list.count,
    order_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = order_list.currency_id)) AS sum_currency_name,
    s.status_name,
    order_list.product_id,
    order_list.status_id,
    order_list.currency_id
   FROM ((order_list
     JOIN products p ON ((p.product_id = order_list.product_id)))
     JOIN status s ON ((s.status_id = order_list.status_id)));


ALTER TABLE order_list_view OWNER TO postgres;

--
-- TOC entry 351 (class 1259 OID 229595)
-- Name: order_raw_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE order_raw_list (
    order_raw_list_id integer NOT NULL,
    order_raw_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE order_raw_list OWNER TO postgres;

--
-- TOC entry 352 (class 1259 OID 229598)
-- Name: order_raw_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW order_raw_list_view AS
 SELECT order_raw_list.order_raw_list_id,
    order_raw_list.order_raw_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    order_raw_list.count,
    order_raw_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = order_raw_list.currency_id)) AS sum_currency_name,
    s.status_name,
    order_raw_list.product_id,
    order_raw_list.status_id,
    order_raw_list.currency_id
   FROM ((order_raw_list
     JOIN products p ON ((p.product_id = order_raw_list.product_id)))
     JOIN status s ON ((s.status_id = order_raw_list.status_id)));


ALTER TABLE order_raw_list_view OWNER TO postgres;

--
-- TOC entry 353 (class 1259 OID 229603)
-- Name: purveyors; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE purveyors (
    user_id integer NOT NULL,
    company_name character varying(100) NOT NULL,
    location_id integer NOT NULL
);


ALTER TABLE purveyors OWNER TO postgres;

--
-- TOC entry 354 (class 1259 OID 229606)
-- Name: order_raws_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW order_raws_view AS
 SELECT order_raws.order_raw_id,
    to_char(order_raws.order_raw_date, 'dd.MM.yyyy hh24:mi'::text) AS order_raw_date,
    to_char(order_raws.execution_date, 'dd.MM.yyyy hh24:mi'::text) AS execution_date,
    s.status_code,
    s.status_name,
    u1.user_name AS purveyor_name,
    u1.user_surname AS purveyor_surname,
    u1.user_phone AS purveyor_phone,
    ( SELECT purveyors.company_name
           FROM purveyors
          WHERE (purveyors.user_id = u1.user_id)) AS purveyor_company_name,
    u2.user_name AS employee_name,
    u2.user_surname AS employee_surname,
    u2.user_phone AS employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u2.user_id)))) AS employee_position_name,
    order_raws.count,
    order_raws.sum,
    c.currency_short_name AS currency_name,
    order_raws.employee_id,
    order_raws.purveyor_id,
    order_raws.status_id,
    order_raws.currency_id
   FROM ((((order_raws
     LEFT JOIN users u1 ON ((u1.user_id = order_raws.purveyor_id)))
     LEFT JOIN users u2 ON ((u2.user_id = order_raws.employee_id)))
     LEFT JOIN status s ON ((s.status_id = order_raws.status_id)))
     LEFT JOIN currencies c ON ((c.currency_id = order_raws.currency_id)));


ALTER TABLE order_raws_view OWNER TO postgres;

--
-- TOC entry 355 (class 1259 OID 229611)
-- Name: orders_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW orders_view AS
 SELECT orders.order_id,
    to_char(orders.order_date, 'dd.MM.yyyy hh24:mi'::text) AS order_date,
    to_char(orders.execution_date, 'dd.MM.yyyy hh24:mi'::text) AS execution_date,
    s.status_code,
    s.status_name,
    u1.user_name AS client_name,
    u1.user_surname AS client_surname,
    u1.user_phone AS client_phone,
    u1.user_address AS clinet_address,
    ( SELECT clients.firm
           FROM clients
          WHERE (clients.user_id = u1.user_id)) AS client_firm,
    u2.user_name AS employee_name,
    u2.user_surname AS employee_surname,
    u2.user_phone AS employee_phone,
    orders.count,
    orders.sum,
    c.currency_short_name AS currency_name,
    orders.employee_id,
    orders.user_id,
    orders.status_id,
    orders.currency_id
   FROM ((((orders
     LEFT JOIN users u1 ON ((u1.user_id = orders.user_id)))
     LEFT JOIN users u2 ON ((u2.user_id = orders.employee_id)))
     LEFT JOIN status s ON ((s.status_id = orders.status_id)))
     LEFT JOIN currencies c ON ((c.currency_id = orders.currency_id)));


ALTER TABLE orders_view OWNER TO postgres;

--
-- TOC entry 356 (class 1259 OID 229616)
-- Name: other_stocks_type; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE other_stocks_type (
    other_stocks_type_id integer NOT NULL,
    other_stocks_type_name character varying(50) NOT NULL,
    other_stocks_type_short_name character varying(10) NOT NULL,
    other_stocks_type_code character varying(15)
);


ALTER TABLE other_stocks_type OWNER TO postgres;

--
-- TOC entry 357 (class 1259 OID 229619)
-- Name: other_stocks_type_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW other_stocks_type_view AS
 SELECT other_stocks_type.other_stocks_type_id,
    other_stocks_type.other_stocks_type_name,
    other_stocks_type.other_stocks_type_short_name,
    other_stocks_type.other_stocks_type_code
   FROM other_stocks_type;


ALTER TABLE other_stocks_type_view OWNER TO postgres;

--
-- TOC entry 358 (class 1259 OID 229623)
-- Name: other_stocks_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW other_stocks_view AS
 SELECT other_stocks.other_stocks_id,
    other_stocks.other_stocks_name,
    other_stocks.price,
    cur.currency_short_name AS currency,
    other_stocks.volume,
    m.measure_short_name AS measure_name,
    c.company_name,
    oths.other_stocks_type_name,
    other_stocks.company_id,
    other_stocks.measure_id,
    other_stocks.currency_id,
    other_stocks.other_stocks_type_id
   FROM ((((other_stocks
     JOIN companies c ON ((c.company_id = other_stocks.company_id)))
     JOIN measures m ON ((m.measure_id = other_stocks.measure_id)))
     JOIN currencies cur ON ((cur.currency_id = other_stocks.currency_id)))
     JOIN other_stocks_type oths ON ((oths.other_stocks_type_id = other_stocks.other_stocks_type_id)))
  ORDER BY other_stocks.other_stocks_name;


ALTER TABLE other_stocks_view OWNER TO postgres;

--
-- TOC entry 359 (class 1259 OID 229628)
-- Name: payment_employee; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE payment_employee (
    payment_employee_id integer NOT NULL,
    payment_id integer NOT NULL,
    employee_id integer NOT NULL
);


ALTER TABLE payment_employee OWNER TO postgres;

--
-- TOC entry 360 (class 1259 OID 229631)
-- Name: payment_employee_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW payment_employee_view AS
 SELECT payment_employee.payment_employee_id,
    payment_employee.payment_id,
    payment_employee.employee_id
   FROM payment_employee;


ALTER TABLE payment_employee_view OWNER TO postgres;

--
-- TOC entry 361 (class 1259 OID 229635)
-- Name: payments_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW payments_view AS
 SELECT payments.payment_id,
    to_char(payments.payment_date, 'dd.MM.yyyy hh24:mi'::text) AS payment_date,
    u.user_name,
    u.user_surname,
    u.user_phone,
    payments.payment_value,
    c.currency_short_name AS currency_name,
    payments.payment_target,
    a.account_number,
    sa.subaccount_number,
    payments.who,
    s.status_name,
    payments.user_id,
    payments.currency_id,
    payments.status_id,
    payments.account_id,
    payments.subaccount_id,
    payments.cashbox_account_id
   FROM (((((payments
     LEFT JOIN currencies c ON ((c.currency_id = payments.currency_id)))
     LEFT JOIN status s ON ((s.status_id = payments.status_id)))
     LEFT JOIN accounts a ON ((a.account_id = payments.account_id)))
     LEFT JOIN subaccounts sa ON ((sa.subaccount_id = payments.subaccount_id)))
     LEFT JOIN users u ON ((u.user_id = payments.user_id)));


ALTER TABLE payments_view OWNER TO postgres;

--
-- TOC entry 362 (class 1259 OID 229640)
-- Name: payslip_order; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE payslip_order (
    payslip_order_id integer NOT NULL,
    payslip_id integer NOT NULL,
    order_id integer
);


ALTER TABLE payslip_order OWNER TO postgres;

--
-- TOC entry 363 (class 1259 OID 229643)
-- Name: payslip_order_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW payslip_order_view AS
 SELECT payslip_order.payslip_order_id,
    payslip_order.payslip_id,
    payslip_order.order_id
   FROM payslip_order;


ALTER TABLE payslip_order_view OWNER TO postgres;

--
-- TOC entry 364 (class 1259 OID 229647)
-- Name: payslips_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW payslips_view AS
 SELECT payslips.payslip_id,
    to_char(payslips.payslip_date, 'dd.MM.yyyy hh24:mi'::text) AS payslip_date,
    payslips.payslip_value,
    c.currency_short_name AS currency_name,
    payslips.salary_id,
    payslips.currency_id
   FROM (payslips
     JOIN currencies c ON ((c.currency_id = payslips.currency_id)));


ALTER TABLE payslips_view OWNER TO postgres;

--
-- TOC entry 365 (class 1259 OID 229651)
-- Name: percent_rate; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE percent_rate (
    percent_rate_id integer NOT NULL,
    value numeric(20,3),
    condition character varying(100),
    position_id integer NOT NULL
);


ALTER TABLE percent_rate OWNER TO postgres;

--
-- TOC entry 366 (class 1259 OID 229654)
-- Name: percent_rate_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW percent_rate_view AS
 SELECT percent_rate.percent_rate_id,
    percent_rate.value,
    percent_rate.condition,
    percent_rate.position_id
   FROM (percent_rate
     JOIN positions p ON ((p.position_id = percent_rate.position_id)));


ALTER TABLE percent_rate_view OWNER TO postgres;

--
-- TOC entry 367 (class 1259 OID 229658)
-- Name: photos; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE photos (
    photo_id integer NOT NULL,
    user_id integer,
    product_id integer,
    photo_source character varying(100)
);


ALTER TABLE photos OWNER TO postgres;

--
-- TOC entry 368 (class 1259 OID 229661)
-- Name: photos_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW photos_view AS
 SELECT photos.photo_id,
    photos.user_id,
    photos.product_id,
    photos.photo_source
   FROM photos;


ALTER TABLE photos_view OWNER TO postgres;

--
-- TOC entry 369 (class 1259 OID 229665)
-- Name: positions_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW positions_view AS
 SELECT positions.position_id,
    positions.position_name
   FROM positions;


ALTER TABLE positions_view OWNER TO postgres;

--
-- TOC entry 370 (class 1259 OID 229669)
-- Name: postging_fixed_assets_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW postging_fixed_assets_view AS
 SELECT posting_fixed_assets.posting_fixed_assets_id,
    users.user_surname,
    ( SELECT coa.name_of_account
           FROM chart_of_accounts coa
          WHERE ((coa.number_of_account)::text = (accounts.account_number)::text)) AS account_name,
    posting_fixed_assets.user_id,
    posting_fixed_assets.subaccount_id,
    posting_fixed_assets.account_id,
    posting_fixed_assets.fixed_assets_id,
    posting_fixed_assets.inventory_id
   FROM ((posting_fixed_assets
     LEFT JOIN users ON ((users.user_id = posting_fixed_assets.user_id)))
     LEFT JOIN accounts ON ((accounts.account_id = posting_fixed_assets.account_id)));


ALTER TABLE postging_fixed_assets_view OWNER TO postgres;

--
-- TOC entry 371 (class 1259 OID 229674)
-- Name: prices; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE prices (
    price_id integer NOT NULL,
    price_date timestamp without time zone NOT NULL,
    price_value numeric(20,5) NOT NULL,
    currency_id integer NOT NULL,
    product_id integer NOT NULL,
    is_outdated boolean
);


ALTER TABLE prices OWNER TO postgres;

--
-- TOC entry 372 (class 1259 OID 229677)
-- Name: prices_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW prices_view AS
 SELECT prices.price_id,
    to_char(prices.price_date, 'dd.MM.yyyy hh24:mi'::text) AS price_date,
    p.product_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    prices.price_value,
    c.currency_short_name AS currency_name,
    prices.currency_id,
    prices.product_id,
    prices.is_outdated
   FROM ((prices
     JOIN products p ON ((p.product_id = prices.product_id)))
     JOIN currencies c ON ((c.currency_id = prices.currency_id)));


ALTER TABLE prices_view OWNER TO postgres;

--
-- TOC entry 373 (class 1259 OID 229682)
-- Name: product_branch; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE product_branch (
    product_branch_id integer NOT NULL,
    product_id integer NOT NULL,
    branch_id integer NOT NULL
);


ALTER TABLE product_branch OWNER TO postgres;

--
-- TOC entry 374 (class 1259 OID 229685)
-- Name: product_branch_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW product_branch_view AS
 SELECT product_branch.product_branch_id,
    b.branch_name,
    b.branch_address,
    p.product_name,
    p.price,
    product_branch.product_id,
    product_branch.branch_id
   FROM ((product_branch
     JOIN products p ON ((p.product_id = product_branch.product_id)))
     JOIN branches b ON ((b.branch_id = product_branch.branch_id)));


ALTER TABLE product_branch_view OWNER TO postgres;

--
-- TOC entry 375 (class 1259 OID 229689)
-- Name: product_type; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE product_type (
    product_type_id integer NOT NULL,
    product_type_name character varying(50) NOT NULL,
    product_type_short_name character varying(10) NOT NULL,
    product_type_code character varying(15)
);


ALTER TABLE product_type OWNER TO postgres;

--
-- TOC entry 376 (class 1259 OID 229692)
-- Name: product_types_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW product_types_view AS
 SELECT product_type.product_type_id,
    product_type.product_type_name,
    product_type.product_type_short_name,
    product_type.product_type_code
   FROM product_type;


ALTER TABLE product_types_view OWNER TO postgres;

--
-- TOC entry 377 (class 1259 OID 229696)
-- Name: production; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE production (
    production_id integer NOT NULL,
    production_date date NOT NULL,
    expiry_date date,
    session_start time without time zone NOT NULL,
    session_end time without time zone
);


ALTER TABLE production OWNER TO postgres;

--
-- TOC entry 378 (class 1259 OID 229699)
-- Name: production_consume_raw_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE production_consume_raw_list (
    consume_raw_list_id integer NOT NULL,
    consume_raw_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE production_consume_raw_list OWNER TO postgres;

--
-- TOC entry 379 (class 1259 OID 229702)
-- Name: production_consume_raw_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW production_consume_raw_list_view AS
 SELECT production_consume_raw_list.consume_raw_list_id,
    production_consume_raw_list.consume_raw_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    production_consume_raw_list.count,
    production_consume_raw_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = production_consume_raw_list.currency_id)) AS sum_currency_name,
    s.status_name,
    production_consume_raw_list.product_id,
    production_consume_raw_list.status_id,
    production_consume_raw_list.currency_id
   FROM ((production_consume_raw_list
     JOIN products p ON ((p.product_id = production_consume_raw_list.product_id)))
     JOIN status s ON ((s.status_id = production_consume_raw_list.status_id)));


ALTER TABLE production_consume_raw_list_view OWNER TO postgres;

--
-- TOC entry 380 (class 1259 OID 229707)
-- Name: production_consume_raws_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW production_consume_raws_view AS
 SELECT production_consume_raws.consume_raw_id,
    to_char(production_consume_raws.consume_raw_date, 'dd.MM.yyyy hh24:mi'::text) AS consume_raw_date,
    to_char(production_consume_raws.execution_date, 'dd.MM.yyyy hh24:mi'::text) AS execution_date,
    s.status_code,
    s.status_name,
    u1.user_name AS employee_name,
    u1.user_surname AS employee_surname,
    u1.user_phone AS employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u1.user_id)))) AS employee_position_name,
    u2.user_name AS stock_employee_name,
    u2.user_surname AS stock_employee_surname,
    u2.user_phone AS stock_employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u2.user_id)))) AS stock_employee_position_name,
    production_consume_raws.count,
    production_consume_raws.sum,
    c.currency_short_name AS currency_name,
    production_consume_raws.employee_id,
    production_consume_raws.user_id,
    production_consume_raws.status_id,
    production_consume_raws.currency_id
   FROM ((((production_consume_raws
     LEFT JOIN users u1 ON ((u1.user_id = production_consume_raws.user_id)))
     LEFT JOIN users u2 ON ((u2.user_id = production_consume_raws.employee_id)))
     LEFT JOIN status s ON ((s.status_id = production_consume_raws.status_id)))
     LEFT JOIN currencies c ON ((c.currency_id = production_consume_raws.currency_id)));


ALTER TABLE production_consume_raws_view OWNER TO postgres;

--
-- TOC entry 381 (class 1259 OID 229712)
-- Name: production_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE production_list (
    production_list_id integer NOT NULL,
    production_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE production_list OWNER TO postgres;

--
-- TOC entry 382 (class 1259 OID 229715)
-- Name: production_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW production_list_view AS
 SELECT production_list.production_list_id,
    production_list.production_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    production_list.count,
    production_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = production_list.currency_id)) AS sum_currency_name,
    s.status_name,
    production_list.product_id,
    production_list.status_id,
    production_list.currency_id
   FROM ((production_list
     JOIN products p ON ((p.product_id = production_list.product_id)))
     JOIN status s ON ((s.status_id = production_list.status_id)));


ALTER TABLE production_list_view OWNER TO postgres;

--
-- TOC entry 383 (class 1259 OID 229720)
-- Name: production_plan; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE production_plan (
    production_plan_id integer NOT NULL,
    production_plan_date timestamp without time zone NOT NULL,
    employee_id integer,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3) NOT NULL,
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE production_plan OWNER TO postgres;

--
-- TOC entry 384 (class 1259 OID 229723)
-- Name: production_plan_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE production_plan_list (
    production_plan_list_id integer NOT NULL,
    production_plan_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE production_plan_list OWNER TO postgres;

--
-- TOC entry 385 (class 1259 OID 229726)
-- Name: production_plan_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW production_plan_list_view AS
 SELECT production_plan_list.production_plan_list_id,
    production_plan_list.production_plan_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    production_plan_list.count,
    production_plan_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = production_plan_list.currency_id)) AS sum_currency_name,
    s.status_name,
    production_plan_list.product_id,
    production_plan_list.status_id,
    production_plan_list.currency_id
   FROM ((production_plan_list
     JOIN products p ON ((p.product_id = production_plan_list.product_id)))
     JOIN status s ON ((s.status_id = production_plan_list.status_id)));


ALTER TABLE production_plan_list_view OWNER TO postgres;

--
-- TOC entry 386 (class 1259 OID 229731)
-- Name: production_plan_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW production_plan_view AS
 SELECT production_plan.production_plan_id,
    to_char(production_plan.production_plan_date, 'dd.MM.yyyy hh24:mi'::text) AS production_plan_date,
    production_plan.count,
    production_plan.sum,
    c.currency_short_name AS currency_name,
    s.status_name,
    e.user_name,
    e.user_surname,
    e.user_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = e.position_id)) AS position_name,
    production_plan.employee_id,
    production_plan.status_id,
    production_plan.currency_id
   FROM (((production_plan
     JOIN employees_view e ON ((e.user_id = production_plan.employee_id)))
     JOIN currencies c ON ((c.currency_id = production_plan.currency_id)))
     JOIN status s ON ((s.status_id = production_plan.status_id)));


ALTER TABLE production_plan_view OWNER TO postgres;

--
-- TOC entry 387 (class 1259 OID 229736)
-- Name: production_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW production_view AS
 SELECT production.production_id,
    to_char((production.production_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS production_date,
    to_char((production.expiry_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS expiry_date,
    to_char(('2001-09-28'::date + (production.session_start)::time with time zone), 'hh24:mi'::text) AS session_start,
    to_char(('2001-09-28'::date + (production.session_end)::time with time zone), 'hh24:mi'::text) AS session_end
   FROM production;


ALTER TABLE production_view OWNER TO postgres;

--
-- TOC entry 388 (class 1259 OID 229740)
-- Name: products_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW products_view AS
 SELECT products.product_id,
    products.product_name,
    products.price,
    cur.currency_short_name AS currency,
    products.volume,
    m.measure_short_name AS measure_name,
    p.product_type_short_name AS product_type_name,
    products.shelf_life,
    c.company_name,
    products.company_id,
    products.measure_id,
    products.product_type_id,
    products.currency_id
   FROM ((((products
     JOIN companies c ON ((c.company_id = products.company_id)))
     JOIN measures m ON ((m.measure_id = products.measure_id)))
     JOIN product_type p ON ((p.product_type_id = products.product_type_id)))
     JOIN currencies cur ON ((cur.currency_id = products.currency_id)))
  ORDER BY products.product_name;


ALTER TABLE products_view OWNER TO postgres;

--
-- TOC entry 389 (class 1259 OID 229745)
-- Name: purveyors_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW purveyors_view AS
 SELECT users.user_id,
    users.user_name,
    users.user_surname,
    users.user_phone,
    ( SELECT locations.country_name
           FROM locations
          WHERE (locations.location_id = purveyors.location_id)) AS country_name,
    ( SELECT locations.region_name
           FROM locations
          WHERE (locations.location_id = purveyors.location_id)) AS region_name,
    ( SELECT locations.city_name
           FROM locations
          WHERE (locations.location_id = purveyors.location_id)) AS city_name,
    users.user_address,
    purveyors.company_name,
    ( SELECT roles.role_name
           FROM roles
          WHERE (roles.role_id = users.role_id)) AS role_name,
    users.password,
    users.user_email,
    users.activated,
    users.role_id,
    purveyors.location_id
   FROM (purveyors
     JOIN users ON ((users.user_id = purveyors.user_id)));


ALTER TABLE purveyors_view OWNER TO postgres;

--
-- TOC entry 390 (class 1259 OID 229750)
-- Name: receipt_other_stocks_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE receipt_other_stocks_list (
    receipt_other_stocks_list_id integer NOT NULL,
    receipt_other_stocks_id integer NOT NULL,
    other_stocks_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE receipt_other_stocks_list OWNER TO postgres;

--
-- TOC entry 391 (class 1259 OID 229753)
-- Name: receipt_other_stocks_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW receipt_other_stocks_list_view AS
 SELECT receipt_other_stocks_list.receipt_other_stocks_list_id,
    receipt_other_stocks_list.receipt_other_stocks_id,
    p.other_stocks_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    receipt_other_stocks_list.count,
    receipt_other_stocks_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = receipt_other_stocks_list.currency_id)) AS sum_currency_name,
    s.status_name,
    receipt_other_stocks_list.other_stocks_id,
    receipt_other_stocks_list.status_id,
    receipt_other_stocks_list.currency_id
   FROM ((receipt_other_stocks_list
     JOIN other_stocks p ON ((p.other_stocks_id = receipt_other_stocks_list.other_stocks_id)))
     JOIN status s ON ((s.status_id = receipt_other_stocks_list.status_id)));


ALTER TABLE receipt_other_stocks_list_view OWNER TO postgres;

--
-- TOC entry 392 (class 1259 OID 229758)
-- Name: receipt_other_stocks_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW receipt_other_stocks_view AS
 SELECT receipt_other_stocks.receipt_other_stocks_id,
    to_char(receipt_other_stocks.receipt_other_stocks_date, 'dd.MM.yyyy hh24:mm'::text) AS receipt_other_stocks_date,
    to_char(receipt_other_stocks.execution_date, 'dd.MM.yyyy hh24:mm'::text) AS execution_date,
    s.status_code,
    s.status_name,
    u1.user_name AS employee_name,
    u1.user_surname AS employee_surname,
    u1.user_phone AS employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u1.user_id)))) AS employee_position_name,
    u2.user_name AS stock_employee_name,
    u2.user_surname AS stock_employee_surname,
    u2.user_phone AS stock_employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u2.user_id)))) AS stock_employee_position_name,
    receipt_other_stocks.count,
    receipt_other_stocks.sum,
    c.currency_short_name AS currency_name,
    receipt_other_stocks.employee_id,
    receipt_other_stocks.user_id,
    receipt_other_stocks.status_id,
    receipt_other_stocks.currency_id
   FROM ((((receipt_other_stocks
     LEFT JOIN users u1 ON ((u1.user_id = receipt_other_stocks.user_id)))
     LEFT JOIN users u2 ON ((u2.user_id = receipt_other_stocks.employee_id)))
     LEFT JOIN status s ON ((s.status_id = receipt_other_stocks.status_id)))
     LEFT JOIN currencies c ON ((c.currency_id = receipt_other_stocks.currency_id)));


ALTER TABLE receipt_other_stocks_view OWNER TO postgres;

--
-- TOC entry 393 (class 1259 OID 229763)
-- Name: receipt_product_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE receipt_product_list (
    receipt_product_list_id integer NOT NULL,
    receipt_product_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE receipt_product_list OWNER TO postgres;

--
-- TOC entry 394 (class 1259 OID 229766)
-- Name: receipt_product_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW receipt_product_list_view AS
 SELECT receipt_product_list.receipt_product_list_id,
    receipt_product_list.receipt_product_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    receipt_product_list.count,
    receipt_product_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = receipt_product_list.currency_id)) AS sum_currency_name,
    s.status_name,
    receipt_product_list.product_id,
    receipt_product_list.status_id,
    receipt_product_list.currency_id
   FROM ((receipt_product_list
     JOIN products p ON ((p.product_id = receipt_product_list.product_id)))
     JOIN status s ON ((s.status_id = receipt_product_list.status_id)));


ALTER TABLE receipt_product_list_view OWNER TO postgres;

--
-- TOC entry 395 (class 1259 OID 229771)
-- Name: receipt_products_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW receipt_products_view AS
 SELECT receipt_products.receipt_product_id,
    to_char(receipt_products.receipt_product_date, 'dd.MM.yyyy hh24:mi'::text) AS receipt_product_date,
    to_char(receipt_products.execution_date, 'dd.MM.yyyy hh24:mi'::text) AS execution_date,
    s.status_code,
    s.status_name,
    u1.user_name AS employee_name,
    u1.user_surname AS employee_surname,
    u1.user_phone AS employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u1.user_id)))) AS employee_position_name,
    u2.user_name AS stock_employee_name,
    u2.user_surname AS stock_employee_surname,
    u2.user_phone AS stock_employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u2.user_id)))) AS stock_employee_position_name,
    receipt_products.count,
    receipt_products.sum,
    c.currency_short_name AS currency_name,
    receipt_products.employee_id,
    receipt_products.user_id,
    receipt_products.status_id,
    receipt_products.currency_id
   FROM ((((receipt_products
     LEFT JOIN users u1 ON ((u1.user_id = receipt_products.user_id)))
     LEFT JOIN users u2 ON ((u2.user_id = receipt_products.employee_id)))
     LEFT JOIN status s ON ((s.status_id = receipt_products.status_id)))
     LEFT JOIN currencies c ON ((c.currency_id = receipt_products.currency_id)));


ALTER TABLE receipt_products_view OWNER TO postgres;

--
-- TOC entry 396 (class 1259 OID 229776)
-- Name: refunds; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE refunds (
    refund_id integer NOT NULL,
    refund_date timestamp without time zone NOT NULL,
    refund_value numeric(20,3) NOT NULL,
    user_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE refunds OWNER TO postgres;

--
-- TOC entry 397 (class 1259 OID 229779)
-- Name: refunds_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW refunds_view AS
 SELECT refunds.refund_id,
    to_char(refunds.refund_date, 'dd.MM.yyyy hh24:mi'::text) AS refund_date,
    refunds.refund_value,
    c.currency_short_name AS currency_name,
    refunds.user_id,
    refunds.currency_id
   FROM (refunds
     JOIN currencies c ON ((c.currency_id = refunds.currency_id)));


ALTER TABLE refunds_view OWNER TO postgres;

--
-- TOC entry 398 (class 1259 OID 229783)
-- Name: relation_type; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE relation_type (
    relation_type_id integer NOT NULL,
    relation_name character varying(30) NOT NULL,
    comment character varying(100)
);


ALTER TABLE relation_type OWNER TO postgres;

--
-- TOC entry 399 (class 1259 OID 229786)
-- Name: relation_type_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW relation_type_view AS
 SELECT relation_type.relation_type_id,
    relation_type.relation_name,
    relation_type.comment
   FROM relation_type;


ALTER TABLE relation_type_view OWNER TO postgres;

--
-- TOC entry 400 (class 1259 OID 229790)
-- Name: relations; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE relations (
    relation_id integer NOT NULL,
    user_id_1 integer NOT NULL,
    user_id_2 integer NOT NULL,
    relation_type_id integer NOT NULL
);


ALTER TABLE relations OWNER TO postgres;

--
-- TOC entry 401 (class 1259 OID 229793)
-- Name: relations_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW relations_view AS
 SELECT relations.relation_id,
    u1.user_name AS employee_name,
    u1.user_surname AS employee_surname,
    u1.user_phone AS employee_phone,
    rt.relation_name,
    u2.user_name,
    u2.user_surname,
    u2.user_phone,
    relations.user_id_1,
    relations.user_id_2,
    relations.relation_type_id
   FROM (((relations
     JOIN users u1 ON ((u1.user_id = relations.user_id_1)))
     JOIN users u2 ON ((u2.user_id = relations.user_id_2)))
     JOIN relation_type rt ON ((rt.relation_type_id = relations.relation_type_id)));


ALTER TABLE relations_view OWNER TO postgres;

--
-- TOC entry 402 (class 1259 OID 229798)
-- Name: return_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE return_list (
    return_list_id integer NOT NULL,
    return_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE return_list OWNER TO postgres;

--
-- TOC entry 403 (class 1259 OID 229801)
-- Name: return_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW return_list_view AS
 SELECT return_list.return_list_id,
    return_list.return_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    return_list.count,
    return_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = return_list.currency_id)) AS sum_currency_name,
    s.status_name,
    return_list.product_id,
    return_list.status_id,
    return_list.currency_id
   FROM ((return_list
     JOIN products p ON ((p.product_id = return_list.product_id)))
     JOIN status s ON ((s.status_id = return_list.status_id)));


ALTER TABLE return_list_view OWNER TO postgres;

--
-- TOC entry 404 (class 1259 OID 229806)
-- Name: returns_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW returns_view AS
 SELECT returns.return_id,
    to_char(returns.return_date, 'dd.MM.yyyy hh24:mi'::text) AS return_date,
    to_char(returns.execution_date, 'dd.MM.yyyy hh24:mi'::text) AS execution_date,
    s.status_code,
    s.status_name,
    u1.user_name AS client_name,
    u1.user_surname AS client_surname,
    u1.user_phone AS client_phone,
    u1.user_address AS clinet_address,
    ( SELECT clients.firm
           FROM clients
          WHERE (clients.user_id = u1.user_id)) AS client_firm,
    u2.user_name AS employee_name,
    u2.user_surname AS employee_surname,
    u2.user_phone AS employee_phone,
    returns.count,
    returns.sum,
    c.currency_short_name AS currency_name,
    returns.employee_id,
    returns.user_id,
    returns.status_id,
    returns.currency_id
   FROM ((((returns
     LEFT JOIN users u1 ON ((u1.user_id = returns.user_id)))
     LEFT JOIN users u2 ON ((u2.user_id = returns.employee_id)))
     LEFT JOIN status s ON ((s.status_id = returns.status_id)))
     LEFT JOIN currencies c ON ((c.currency_id = returns.currency_id)));


ALTER TABLE returns_view OWNER TO postgres;

--
-- TOC entry 405 (class 1259 OID 229811)
-- Name: roles_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW roles_view AS
 SELECT roles.role_id,
    roles.role_code,
    roles.role_name,
    roles.comment
   FROM roles;


ALTER TABLE roles_view OWNER TO postgres;

--
-- TOC entry 406 (class 1259 OID 229815)
-- Name: salaries; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE salaries (
    salary_id integer NOT NULL,
    user_id integer NOT NULL,
    salary_value numeric(20,3) NOT NULL,
    currency_id integer NOT NULL,
    salary_type_id integer NOT NULL,
    salary_date timestamp without time zone NOT NULL,
    salary_bonus boolean
);


ALTER TABLE salaries OWNER TO postgres;

--
-- TOC entry 407 (class 1259 OID 229818)
-- Name: salary_type; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE salary_type (
    salary_type_id integer NOT NULL,
    salary_type_code character varying(15) NOT NULL,
    salary_type_name character varying(30) NOT NULL
);


ALTER TABLE salary_type OWNER TO postgres;

--
-- TOC entry 408 (class 1259 OID 229821)
-- Name: salaries_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW salaries_view AS
 SELECT salaries.salary_id,
    salaries.user_id,
    u.user_name,
    u.user_surname,
    u.user_phone,
    to_char(salaries.salary_date, 'dd.MM.yyyy hh24:mi'::text) AS salary_date,
    salaries.salary_value,
    c.currency_short_name AS currency_name,
    s.salary_type_name,
    salaries.currency_id,
    salaries.salary_type_id,
    salaries.salary_bonus
   FROM (((salaries
     JOIN users u ON ((u.user_id = salaries.user_id)))
     JOIN currencies c ON ((c.currency_id = salaries.currency_id)))
     JOIN salary_type s ON ((s.salary_type_id = salaries.salary_type_id)));


ALTER TABLE salaries_view OWNER TO postgres;

--
-- TOC entry 409 (class 1259 OID 229826)
-- Name: salary_type_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW salary_type_view AS
 SELECT salary_type.salary_type_id,
    salary_type.salary_type_code,
    salary_type.salary_type_name
   FROM salary_type;


ALTER TABLE salary_type_view OWNER TO postgres;

--
-- TOC entry 410 (class 1259 OID 229830)
-- Name: shareholders; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE shareholders (
    user_id integer NOT NULL,
    count_of_stock numeric(20,3),
    informaton character varying(100)
);


ALTER TABLE shareholders OWNER TO postgres;

--
-- TOC entry 411 (class 1259 OID 229833)
-- Name: shareholders_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW shareholders_view AS
 SELECT shareholders.user_id,
    users.user_name,
    users.user_surname,
    users.user_phone,
    users.user_address,
    shareholders.count_of_stock,
    shareholders.informaton
   FROM (shareholders
     JOIN users ON ((users.user_id = shareholders.user_id)));


ALTER TABLE shareholders_view OWNER TO postgres;

--
-- TOC entry 412 (class 1259 OID 229837)
-- Name: specification_change_log; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE specification_change_log (
    specification_change_log_id integer NOT NULL,
    specification_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(20,5) NOT NULL,
    log_date timestamp without time zone,
    user_id integer
);


ALTER TABLE specification_change_log OWNER TO postgres;

--
-- TOC entry 413 (class 1259 OID 229840)
-- Name: specification_change_log_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW specification_change_log_view AS
 SELECT specification_change_log.specification_change_log_id,
    specification_change_log.specification_id,
    specification_change_log.product_id,
    specification_change_log.count,
    to_char(specification_change_log.log_date, 'dd.MM.yyyy hh24:mi'::text) AS log_date,
    specification_change_log.user_id
   FROM specification_change_log;


ALTER TABLE specification_change_log_view OWNER TO postgres;

--
-- TOC entry 414 (class 1259 OID 229844)
-- Name: specification_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE specification_list (
    specification_list_id integer NOT NULL,
    specification_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(20,5) NOT NULL
);


ALTER TABLE specification_list OWNER TO postgres;

--
-- TOC entry 415 (class 1259 OID 229847)
-- Name: specification_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW specification_list_view AS
 SELECT specification_list.specification_list_id,
    specification_list.specification_id,
    p.product_name,
    specification_list.count,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    specification_list.product_id
   FROM (specification_list
     JOIN products p ON ((p.product_id = specification_list.product_id)));


ALTER TABLE specification_list_view OWNER TO postgres;

--
-- TOC entry 416 (class 1259 OID 229851)
-- Name: specifications; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE specifications (
    specification_id integer NOT NULL,
    product_id integer NOT NULL,
    sum numeric(20,3) NOT NULL,
    currency_id integer NOT NULL,
    employee_id integer NOT NULL,
    specification_date timestamp without time zone NOT NULL
);


ALTER TABLE specifications OWNER TO postgres;

--
-- TOC entry 417 (class 1259 OID 229855)
-- Name: specifications_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW specifications_view AS
 SELECT specifications.specification_id,
    to_char(specifications.specification_date, 'dd.MM.yyyy hh24:mi'::text) AS specification_date,
    p.product_name,
    specifications.sum,
    c.currency_short_name AS currency_name,
    u.user_name AS employee_name,
    u.user_surname AS employee_surname,
    u.user_phone AS employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u.user_id)))) AS employee_position_name,
    specifications.product_id,
    specifications.currency_id,
    specifications.employee_id
   FROM (((specifications
     LEFT JOIN products p ON ((p.product_id = specifications.product_id)))
     LEFT JOIN users u ON ((u.user_id = specifications.employee_id)))
     LEFT JOIN currencies c ON ((c.currency_id = specifications.currency_id)));


ALTER TABLE specifications_view OWNER TO postgres;

--
-- TOC entry 418 (class 1259 OID 229860)
-- Name: spoilage_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE spoilage_list (
    spoilage_list_id integer NOT NULL,
    spoilage_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE spoilage_list OWNER TO postgres;

--
-- TOC entry 419 (class 1259 OID 229863)
-- Name: spoilage_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW spoilage_list_view AS
 SELECT spoilage_list.spoilage_list_id,
    spoilage_list.spoilage_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    spoilage_list.count,
    spoilage_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = spoilage_list.currency_id)) AS sum_currency_name,
    s.status_name,
    spoilage_list.product_id,
    spoilage_list.status_id,
    spoilage_list.currency_id
   FROM ((spoilage_list
     JOIN products p ON ((p.product_id = spoilage_list.product_id)))
     JOIN status s ON ((s.status_id = spoilage_list.status_id)));


ALTER TABLE spoilage_list_view OWNER TO postgres;

--
-- TOC entry 420 (class 1259 OID 229868)
-- Name: spoilage_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW spoilage_view AS
 SELECT spoilage.spoilage_id,
    to_char(spoilage.spoilage_date, 'dd.MM.yyyy hh24:mi'::text) AS spoilage_date,
    spoilage.count,
    spoilage.sum,
    c.currency_short_name AS currency_name,
    s.status_name,
    e.user_name,
    e.user_surname,
    e.user_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = e.position_id)) AS position_name,
    spoilage.employee_id,
    spoilage.status_id,
    spoilage.currency_id
   FROM (((spoilage
     LEFT JOIN employees_view e ON ((e.user_id = spoilage.employee_id)))
     LEFT JOIN currencies c ON ((c.currency_id = spoilage.currency_id)))
     LEFT JOIN status s ON ((s.status_id = spoilage.status_id)));


ALTER TABLE spoilage_view OWNER TO postgres;

--
-- TOC entry 421 (class 1259 OID 229873)
-- Name: state; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE state (
    state_id integer NOT NULL,
    universal_id integer NOT NULL,
    status_id integer NOT NULL,
    last_change timestamp with time zone
);


ALTER TABLE state OWNER TO postgres;

--
-- TOC entry 422 (class 1259 OID 229876)
-- Name: state_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW state_view AS
 SELECT state.state_id,
    state.universal_id,
    state.status_id,
    to_char(state.last_change, 'dd.MM.yyyy hh24:mi'::text) AS last_change
   FROM state;


ALTER TABLE state_view OWNER TO postgres;

--
-- TOC entry 423 (class 1259 OID 229880)
-- Name: status_rule; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE status_rule (
    status_rule_id integer NOT NULL,
    operation character varying(50) NOT NULL,
    status_id integer NOT NULL
);


ALTER TABLE status_rule OWNER TO postgres;

--
-- TOC entry 424 (class 1259 OID 229883)
-- Name: status_rule_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW status_rule_view AS
 SELECT status_rule.status_rule_id,
    status_rule.operation,
    s.status_name,
    status_rule.status_id
   FROM (status_rule
     JOIN status s ON ((s.status_id = status_rule.status_id)));


ALTER TABLE status_rule_view OWNER TO postgres;

--
-- TOC entry 425 (class 1259 OID 229887)
-- Name: status_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW status_view AS
 SELECT status.status_id,
    status.status_code,
    status.status_name,
    status.comment
   FROM status;


ALTER TABLE status_view OWNER TO postgres;

--
-- TOC entry 426 (class 1259 OID 229891)
-- Name: stock; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE stock (
    stock_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL,
    warehouse_id integer
);


ALTER TABLE stock OWNER TO postgres;

--
-- TOC entry 427 (class 1259 OID 229894)
-- Name: stock_change_log; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE stock_change_log (
    stock_change_log_id integer NOT NULL,
    stock_id integer NOT NULL,
    product_id integer,
    count numeric(15,5),
    sum numeric(20,3),
    status_id integer,
    currency_id integer,
    warehouse_id integer,
    log_date timestamp without time zone,
    user_id integer,
    operation_id integer
);


ALTER TABLE stock_change_log OWNER TO postgres;

--
-- TOC entry 428 (class 1259 OID 229897)
-- Name: stock_change_log_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW stock_change_log_view AS
 SELECT stock_change_log.stock_change_log_id,
    stock_change_log.stock_id,
    stock_change_log.product_id,
    stock_change_log.count,
    stock_change_log.sum,
    stock_change_log.status_id,
    stock_change_log.currency_id,
    stock_change_log.warehouse_id,
    to_char(stock_change_log.log_date, 'dd.MM.yyyy hh24:mi'::text) AS log_date,
    stock_change_log.user_id,
    stock_change_log.operation_id
   FROM stock_change_log;


ALTER TABLE stock_change_log_view OWNER TO postgres;

--
-- TOC entry 429 (class 1259 OID 229901)
-- Name: stock_history; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE stock_history (
    stock_id integer NOT NULL,
    product_id integer,
    count numeric(15,5),
    sum numeric(20,3),
    status_id integer,
    currency_id integer,
    warehouse_id integer,
    history_date timestamp without time zone
);


ALTER TABLE stock_history OWNER TO postgres;

--
-- TOC entry 430 (class 1259 OID 229904)
-- Name: stock_history_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW stock_history_view AS
 SELECT stock_history.stock_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    stock_history.count,
    stock_history.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = stock_history.currency_id)) AS sum_currency_name,
    w.warehouse_name,
    ( SELECT subaccounts.subaccount_number
           FROM subaccounts
          WHERE (subaccounts.subaccount_id = w.subaccount_id)) AS subaccount_number,
    s.status_name,
    stock_history.product_id,
    stock_history.status_id,
    stock_history.currency_id,
    stock_history.warehouse_id,
    to_char(stock_history.history_date, 'dd.MM.yyyy hh24:mi'::text) AS history_date
   FROM (((stock_history
     LEFT JOIN products p ON ((p.product_id = stock_history.product_id)))
     LEFT JOIN status s ON ((s.status_id = stock_history.status_id)))
     LEFT JOIN warehouse w ON ((w.warehouse_id = stock_history.warehouse_id)));


ALTER TABLE stock_history_view OWNER TO postgres;

--
-- TOC entry 431 (class 1259 OID 229909)
-- Name: stock_limit; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE stock_limit (
    stock_limit_id integer NOT NULL,
    stock_id integer,
    product_id integer,
    min_value numeric(20,3),
    max_value numeric(20,3)
);


ALTER TABLE stock_limit OWNER TO postgres;

--
-- TOC entry 432 (class 1259 OID 229912)
-- Name: stock_limit_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW stock_limit_view AS
 SELECT stock_limit.stock_limit_id,
    ( SELECT warehouse.warehouse_name
           FROM warehouse
          WHERE (warehouse.warehouse_id = stock.warehouse_id)) AS warehouse_name,
    products.product_name,
    stock_limit.min_value,
    stock_limit.max_value,
    stock_limit.stock_id,
    stock_limit.product_id
   FROM ((stock_limit
     LEFT JOIN stock ON ((stock.stock_id = stock_limit.stock_id)))
     LEFT JOIN products ON ((products.product_id = stock_limit.product_id)));


ALTER TABLE stock_limit_view OWNER TO postgres;

--
-- TOC entry 433 (class 1259 OID 229917)
-- Name: stock_transfer_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE stock_transfer_list (
    stock_transfer_list_id integer NOT NULL,
    stock_transfer_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE stock_transfer_list OWNER TO postgres;

--
-- TOC entry 434 (class 1259 OID 229920)
-- Name: stock_transfer_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW stock_transfer_list_view AS
 SELECT stock_transfer_list.stock_transfer_list_id,
    stock_transfer_list.stock_transfer_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    stock_transfer_list.count,
    stock_transfer_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = stock_transfer_list.currency_id)) AS sum_currency_name,
    s.status_name,
    stock_transfer_list.product_id,
    stock_transfer_list.status_id,
    stock_transfer_list.currency_id
   FROM ((stock_transfer_list
     JOIN products p ON ((p.product_id = stock_transfer_list.product_id)))
     JOIN status s ON ((s.status_id = stock_transfer_list.status_id)));


ALTER TABLE stock_transfer_list_view OWNER TO postgres;

--
-- TOC entry 435 (class 1259 OID 229925)
-- Name: stock_transfers_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW stock_transfers_view AS
 SELECT stock_transfers.stock_transfer_id,
    to_char(stock_transfers.stock_transfer_date, 'dd.MM.yyyy hh24:mi'::text) AS stock_transfer_date,
    to_char(stock_transfers.execution_date, 'dd.MM.yyyy hh24:mi'::text) AS execution_date,
    s.status_code,
    s.status_name,
    u1.user_name AS employee_name,
    u1.user_surname AS employee_surname,
    u1.user_phone AS employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u1.user_id)))) AS employee_position_name,
    u2.user_name AS stock_employee_name,
    u2.user_surname AS stock_employee_surname,
    u2.user_phone AS stock_employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u2.user_id)))) AS stock_employee_position_name,
    stock_transfers.count,
    stock_transfers.sum,
    c.currency_short_name AS currency_name,
    stock_transfers.employee_id,
    stock_transfers.user_id,
    stock_transfers.status_id,
    stock_transfers.currency_id
   FROM ((((stock_transfers
     LEFT JOIN users u1 ON ((u1.user_id = stock_transfers.user_id)))
     LEFT JOIN users u2 ON ((u2.user_id = stock_transfers.employee_id)))
     LEFT JOIN status s ON ((s.status_id = stock_transfers.status_id)))
     LEFT JOIN currencies c ON ((c.currency_id = stock_transfers.currency_id)));


ALTER TABLE stock_transfers_view OWNER TO postgres;

--
-- TOC entry 436 (class 1259 OID 229930)
-- Name: stock_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW stock_view AS
 SELECT stock.stock_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    stock.count,
    stock.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = stock.currency_id)) AS sum_currency_name,
    w.warehouse_name,
    ( SELECT subaccounts.subaccount_number
           FROM subaccounts
          WHERE (subaccounts.subaccount_id = w.subaccount_id)) AS subaccount_number,
    s.status_name,
    stock.product_id,
    stock.status_id,
    stock.currency_id,
    stock.warehouse_id
   FROM (((stock
     JOIN products p ON ((p.product_id = stock.product_id)))
     JOIN status s ON ((s.status_id = stock.status_id)))
     JOIN warehouse w ON ((w.warehouse_id = stock.warehouse_id)))
  ORDER BY p.product_name;


ALTER TABLE stock_view OWNER TO postgres;

--
-- TOC entry 437 (class 1259 OID 229935)
-- Name: subaccount_change_log; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE subaccount_change_log (
    subaccount_change_log_id integer NOT NULL,
    subaccount_id integer NOT NULL,
    start_balance numeric(20,3) NOT NULL,
    current_balance numeric(20,3) NOT NULL,
    log_date timestamp without time zone,
    user_id integer,
    operation_id integer
);


ALTER TABLE subaccount_change_log OWNER TO postgres;

--
-- TOC entry 438 (class 1259 OID 229938)
-- Name: subaccount_change_log_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW subaccount_change_log_view AS
 SELECT subaccount_change_log.subaccount_change_log_id,
    subaccount_change_log.subaccount_id,
    subaccount_change_log.start_balance,
    subaccount_change_log.current_balance,
    to_char(subaccount_change_log.log_date, 'dd.MM.yyyy hh24:mi'::text) AS log_date,
    subaccount_change_log.user_id,
    subaccount_change_log.operation_id
   FROM subaccount_change_log;


ALTER TABLE subaccount_change_log_view OWNER TO postgres;

--
-- TOC entry 439 (class 1259 OID 229942)
-- Name: subaccount_history; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE subaccount_history (
    subaccount_history_id integer NOT NULL,
    subaccount_id integer NOT NULL,
    start_balance numeric(20,3) NOT NULL,
    current_balance numeric(20,3) NOT NULL,
    from_date date,
    till_date date
);


ALTER TABLE subaccount_history OWNER TO postgres;

--
-- TOC entry 440 (class 1259 OID 229945)
-- Name: subaccount_history_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW subaccount_history_view AS
 SELECT subaccount_history.subaccount_history_id,
    subaccount_history.subaccount_id,
    subaccount_history.start_balance,
    subaccount_history.current_balance,
    to_char((subaccount_history.from_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS from_date,
    to_char((subaccount_history.till_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS till_date
   FROM subaccount_history;


ALTER TABLE subaccount_history_view OWNER TO postgres;

--
-- TOC entry 441 (class 1259 OID 229949)
-- Name: subaccount_limit; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE subaccount_limit (
    subaccount_limit_id integer NOT NULL,
    subaccount_id integer NOT NULL,
    min_value numeric(20,3),
    max_value numeric(20,3)
);


ALTER TABLE subaccount_limit OWNER TO postgres;

--
-- TOC entry 442 (class 1259 OID 229952)
-- Name: subaccount_limit_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW subaccount_limit_view AS
 SELECT subaccount_limit.subaccount_limit_id,
    subaccounts.subaccount_number,
    subaccount_limit.subaccount_id,
    subaccount_limit.min_value,
    subaccount_limit.max_value
   FROM (subaccount_limit
     LEFT JOIN subaccounts ON ((subaccounts.subaccount_id = subaccount_limit.subaccount_id)));


ALTER TABLE subaccount_limit_view OWNER TO postgres;

--
-- TOC entry 443 (class 1259 OID 229956)
-- Name: subaccounts_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW subaccounts_view AS
 SELECT subaccounts.subaccount_id,
    a.account_id,
    a.account_number,
    subaccounts.subaccount_number,
    subaccounts.start_balance,
    subaccounts.current_balance,
    c.currency_short_name AS currency_name,
    s.status_name,
    subaccounts.currency_id,
    subaccounts.status_id,
    to_char((subaccounts.date_opened)::timestamp with time zone, 'dd.MM.yyyy'::text) AS date_opened,
    to_char((subaccounts.date_closed)::timestamp with time zone, 'dd.MM.yyyy'::text) AS date_closed,
    subaccounts.details
   FROM (((subaccounts
     JOIN accounts a ON ((a.account_id = subaccounts.account_id)))
     JOIN currencies c ON ((c.currency_id = subaccounts.currency_id)))
     JOIN status s ON ((s.status_id = subaccounts.status_id)));


ALTER TABLE subaccounts_view OWNER TO postgres;

--
-- TOC entry 444 (class 1259 OID 229961)
-- Name: taxes; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE taxes (
    tax_id integer NOT NULL,
    tax_name character(100) NOT NULL,
    tax_code character varying(15) NOT NULL,
    fixed_value numeric(20,3),
    percent_value integer,
    formula_value character varying(100)
);


ALTER TABLE taxes OWNER TO postgres;

--
-- TOC entry 445 (class 1259 OID 229964)
-- Name: taxes_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW taxes_view AS
 SELECT taxes.tax_id,
    taxes.tax_name,
    taxes.tax_code,
    taxes.fixed_value,
    taxes.percent_value,
    taxes.formula_value
   FROM taxes;


ALTER TABLE taxes_view OWNER TO postgres;

--
-- TOC entry 446 (class 1259 OID 229968)
-- Name: timesheet; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE timesheet (
    timesheet_id integer NOT NULL,
    salary_id integer NOT NULL,
    worked_time numeric(4,2) NOT NULL,
    timesheet_date date NOT NULL
);


ALTER TABLE timesheet OWNER TO postgres;

--
-- TOC entry 447 (class 1259 OID 229971)
-- Name: timesheet_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW timesheet_view AS
 SELECT timesheet.timesheet_id,
    s.user_name,
    s.user_surname,
    s.user_phone,
    to_char((timesheet.timesheet_date)::timestamp with time zone, 'dd.MM.yyyy'::text) AS timesheet_date,
    timesheet.worked_time,
    timesheet.salary_id
   FROM (timesheet
     JOIN salaries_view s ON ((s.salary_id = timesheet.salary_id)));


ALTER TABLE timesheet_view OWNER TO postgres;

--
-- TOC entry 448 (class 1259 OID 229975)
-- Name: transport_change_log; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE transport_change_log (
    transport_change_log_id integer NOT NULL,
    transport_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL,
    log_date timestamp without time zone,
    user_id integer,
    operation_id integer
);


ALTER TABLE transport_change_log OWNER TO postgres;

--
-- TOC entry 449 (class 1259 OID 229978)
-- Name: transport_change_log_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW transport_change_log_view AS
 SELECT transport_change_log.transport_change_log_id,
    transport_change_log.transport_id,
    transport_change_log.product_id,
    transport_change_log.count,
    transport_change_log.sum,
    transport_change_log.status_id,
    transport_change_log.currency_id,
    to_char(transport_change_log.log_date, 'dd.MM.yyyy hh24:mi'::text) AS log_date,
    transport_change_log.user_id,
    transport_change_log.operation_id
   FROM transport_change_log;


ALTER TABLE transport_change_log_view OWNER TO postgres;

--
-- TOC entry 450 (class 1259 OID 229982)
-- Name: transport_history; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE transport_history (
    transport_history_id integer NOT NULL,
    transport_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL,
    from_date date,
    till_date date
);


ALTER TABLE transport_history OWNER TO postgres;

--
-- TOC entry 451 (class 1259 OID 229985)
-- Name: transport_history_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW transport_history_view AS
 SELECT transport_history.transport_history_id,
    transport_history.transport_id,
    transport_history.product_id,
    transport_history.count,
    transport_history.sum,
    transport_history.status_id,
    transport_history.currency_id,
    transport_history.from_date,
    transport_history.till_date
   FROM transport_history;


ALTER TABLE transport_history_view OWNER TO postgres;

--
-- TOC entry 452 (class 1259 OID 229989)
-- Name: transport_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE transport_list (
    transport_list_id integer NOT NULL,
    transport_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE transport_list OWNER TO postgres;

--
-- TOC entry 453 (class 1259 OID 229992)
-- Name: transport_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW transport_list_view AS
 SELECT transport_list.transport_list_id,
    transport_list.transport_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    transport_list.count,
    transport_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = transport_list.currency_id)) AS sum_currency_name,
    s.status_name,
    transport_list.product_id,
    transport_list.status_id,
    transport_list.currency_id
   FROM ((transport_list
     JOIN products p ON ((p.product_id = transport_list.product_id)))
     JOIN status s ON ((s.status_id = transport_list.status_id)));


ALTER TABLE transport_list_view OWNER TO postgres;

--
-- TOC entry 454 (class 1259 OID 229997)
-- Name: transports; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE transports (
    transport_id integer NOT NULL,
    user_id integer,
    transport_date timestamp without time zone,
    execution_date timestamp(0) without time zone,
    employee_id integer NOT NULL,
    count numeric(15,5),
    sum numeric(20,3),
    status_id integer,
    currency_id integer
);


ALTER TABLE transports OWNER TO postgres;

--
-- TOC entry 455 (class 1259 OID 230000)
-- Name: transports_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW transports_view AS
 SELECT transports.transport_id,
    to_char(transports.transport_date, 'dd.MM.yyyy hh24:mi'::text) AS transport_date,
    to_char(transports.execution_date, 'dd.MM.yyyy hh24:mi'::text) AS execution_date,
    s.status_code,
    s.status_name,
    u1.user_name,
    u1.user_surname,
    u1.user_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u1.user_id)))) AS user_position_name,
    u2.user_name AS employee_name,
    u2.user_surname AS employee_surname,
    u2.user_phone AS employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u2.user_id)))) AS employee_position_name,
    transports.count,
    transports.sum,
    c.currency_short_name AS currency_name,
    transports.employee_id,
    transports.user_id,
    transports.status_id,
    transports.currency_id
   FROM ((((transports
     LEFT JOIN users u1 ON ((u1.user_id = transports.user_id)))
     LEFT JOIN users u2 ON ((u2.user_id = transports.employee_id)))
     LEFT JOIN status s ON ((s.status_id = transports.status_id)))
     LEFT JOIN currencies c ON ((c.currency_id = transports.currency_id)));


ALTER TABLE transports_view OWNER TO postgres;

--
-- TOC entry 456 (class 1259 OID 230005)
-- Name: user_branch_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW user_branch_view AS
 SELECT users.user_id,
    users.user_email,
    users.user_name,
    users.user_surname,
    users.user_phone,
    users.user_address,
    users.role_id,
    users.password,
    users.activated,
    company_employee.company_employee_id,
    company_employee.company_id,
    company_employee.employee_id,
    company_employee.branch_id
   FROM (users
     LEFT JOIN company_employee ON ((company_employee.employee_id = users.user_id)));


ALTER TABLE user_branch_view OWNER TO postgres;

--
-- TOC entry 457 (class 1259 OID 230009)
-- Name: user_extended_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW user_extended_view AS
 SELECT users.user_id,
    users.user_name,
    users.user_surname,
    users.user_phone,
    users.user_address,
    c.company_name,
    br.branch_name,
    r.role_name,
    s.subaccount_number,
    users.role_id,
    s.subaccount_id,
    s.account_id,
    company_employee.company_id,
    company_employee.branch_id
   FROM ((((((users
     LEFT JOIN roles r ON ((r.role_id = users.role_id)))
     LEFT JOIN balances b ON ((b.user_id = users.user_id)))
     LEFT JOIN subaccounts s ON ((s.subaccount_id = b.subaccount_id)))
     LEFT JOIN company_employee ON ((company_employee.employee_id = users.user_id)))
     LEFT JOIN companies c ON ((c.company_id = company_employee.company_id)))
     LEFT JOIN branches br ON ((br.branch_id = company_employee.branch_id)));


ALTER TABLE user_extended_view OWNER TO postgres;

--
-- TOC entry 458 (class 1259 OID 230014)
-- Name: user_group; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE user_group (
    user_group_id integer NOT NULL,
    group_id integer,
    user_id integer
);


ALTER TABLE user_group OWNER TO postgres;

--
-- TOC entry 459 (class 1259 OID 230017)
-- Name: user_group_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW user_group_view AS
 SELECT user_group.user_group_id,
    groups.group_name,
    users.user_surname,
    users.user_name,
    users.role_id,
    user_group.group_id,
    user_group.user_id
   FROM ((user_group
     LEFT JOIN groups ON ((groups.group_id = user_group.group_id)))
     LEFT JOIN users ON ((users.user_id = user_group.user_id)));


ALTER TABLE user_group_view OWNER TO postgres;

--
-- TOC entry 460 (class 1259 OID 230021)
-- Name: users_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW users_view AS
 SELECT users.user_id,
    users.user_email,
    users.user_name,
    users.user_surname,
    users.user_phone,
    users.user_address,
    r.role_name,
    users.password,
    users.activated,
    users.role_id
   FROM (users
     JOIN roles r ON ((r.role_id = users.role_id)));


ALTER TABLE users_view OWNER TO postgres;

--
-- TOC entry 461 (class 1259 OID 230025)
-- Name: warehouse_employee; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE warehouse_employee (
    warehouse_employee_id integer NOT NULL,
    warehouse_id integer NOT NULL,
    employee_id integer NOT NULL
);


ALTER TABLE warehouse_employee OWNER TO postgres;

--
-- TOC entry 462 (class 1259 OID 230028)
-- Name: warehouse_employee_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW warehouse_employee_view AS
 SELECT warehouse_employee.warehouse_employee_id,
    u.user_name,
    u.user_surname,
    u.user_phone,
    ( SELECT roles.role_name
           FROM roles
          WHERE (roles.role_id = u.role_id)) AS role_name,
    w.warehouse_name,
    ( SELECT subaccounts.subaccount_number
           FROM subaccounts
          WHERE (subaccounts.subaccount_id = w.subaccount_id)) AS subaccount_number,
    warehouse_employee.warehouse_id,
    warehouse_employee.employee_id
   FROM ((warehouse_employee
     JOIN warehouse w ON ((w.warehouse_id = warehouse_employee.warehouse_id)))
     JOIN users u ON ((u.user_id = warehouse_employee.employee_id)));


ALTER TABLE warehouse_employee_view OWNER TO postgres;

--
-- TOC entry 463 (class 1259 OID 230033)
-- Name: warehouse_type; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE warehouse_type (
    warehouse_type_id integer NOT NULL,
    warehouse_type_code character varying(20) NOT NULL,
    warehouse_type_purpose character varying(60),
    warehouse_type_name character varying(60) NOT NULL
);


ALTER TABLE warehouse_type OWNER TO postgres;

--
-- TOC entry 464 (class 1259 OID 230036)
-- Name: warehouse_type_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW warehouse_type_view AS
 SELECT warehouse_type.warehouse_type_id,
    warehouse_type.warehouse_type_code,
    warehouse_type.warehouse_type_purpose,
    warehouse_type.warehouse_type_name
   FROM warehouse_type;


ALTER TABLE warehouse_type_view OWNER TO postgres;

--
-- TOC entry 465 (class 1259 OID 230040)
-- Name: warehouse_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW warehouse_view AS
 SELECT warehouse.warehouse_id,
    warehouse.warehouse_name,
    s.subaccount_number,
    wt.warehouse_type_name,
    warehouse.warehouse_address,
    warehouse.warehouse_phone,
    warehouse.warehouse_type_id,
    warehouse.subaccount_id
   FROM ((warehouse
     JOIN warehouse_type wt ON ((wt.warehouse_type_id = warehouse.warehouse_type_id)))
     JOIN subaccounts s ON ((s.subaccount_id = warehouse.subaccount_id)));


ALTER TABLE warehouse_view OWNER TO postgres;

--
-- TOC entry 466 (class 1259 OID 230045)
-- Name: withdrawals_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW withdrawals_view AS
 SELECT withdrawals.withdrawal_id,
    to_char(withdrawals.withdrawal_date, 'dd.MM.yyyy hh24:mi'::text) AS withdrawal_date,
    withdrawals.withdrawal_value,
    c.currency_short_name AS currency_name,
    u.user_name,
    u.user_surname,
    u.user_phone,
    st.status_name,
    a.account_number,
    s.subaccount_number,
    withdrawals.who,
    withdrawals.withdrawal_target,
    withdrawals.user_id,
    withdrawals.currency_id,
    withdrawals.subaccount_id,
    st.status_id,
    a.account_id,
    withdrawals.cashbox_account_id
   FROM (((((withdrawals
     LEFT JOIN users u ON ((u.user_id = withdrawals.user_id)))
     LEFT JOIN currencies c ON ((c.currency_id = withdrawals.currency_id)))
     LEFT JOIN status st ON ((st.status_id = withdrawals.status_id)))
     LEFT JOIN subaccounts s ON ((s.subaccount_id = withdrawals.subaccount_id)))
     LEFT JOIN accounts a ON ((a.account_id = withdrawals.account_id)));


ALTER TABLE withdrawals_view OWNER TO postgres;

--
-- TOC entry 467 (class 1259 OID 230050)
-- Name: write_off_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE write_off_list (
    write_off_list_id integer NOT NULL,
    write_off_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE write_off_list OWNER TO postgres;

--
-- TOC entry 468 (class 1259 OID 230053)
-- Name: write_off_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW write_off_list_view AS
 SELECT write_off_list.write_off_list_id,
    write_off_list.write_off_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    write_off_list.count,
    write_off_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = write_off_list.currency_id)) AS sum_currency_name,
    s.status_name,
    write_off_list.product_id,
    write_off_list.status_id,
    write_off_list.currency_id
   FROM ((write_off_list
     JOIN products p ON ((p.product_id = write_off_list.product_id)))
     JOIN status s ON ((s.status_id = write_off_list.status_id)));


ALTER TABLE write_off_list_view OWNER TO postgres;

--
-- TOC entry 469 (class 1259 OID 230058)
-- Name: write_off_raw_list; Type: TABLE; Schema: OrmasSchema; Owner: postgres
--

CREATE TABLE write_off_raw_list (
    write_off_raw_list_id integer NOT NULL,
    write_off_raw_id integer NOT NULL,
    product_id integer NOT NULL,
    count numeric(15,5) NOT NULL,
    sum numeric(20,3),
    status_id integer NOT NULL,
    currency_id integer NOT NULL
);


ALTER TABLE write_off_raw_list OWNER TO postgres;

--
-- TOC entry 470 (class 1259 OID 230061)
-- Name: write_off_raw_list_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW write_off_raw_list_view AS
 SELECT write_off_raw_list.write_off_raw_list_id,
    write_off_raw_list.write_off_raw_id,
    p.product_name,
    p.price,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = p.currency_id)) AS currency_name,
    p.volume,
    ( SELECT measures.measure_name
           FROM measures
          WHERE (measures.measure_id = p.measure_id)) AS measure_name,
    write_off_raw_list.count,
    write_off_raw_list.sum,
    ( SELECT currencies.currency_short_name
           FROM currencies
          WHERE (currencies.currency_id = write_off_raw_list.currency_id)) AS sum_currency_name,
    s.status_name,
    write_off_raw_list.product_id,
    write_off_raw_list.status_id,
    write_off_raw_list.currency_id
   FROM ((write_off_raw_list
     JOIN products p ON ((p.product_id = write_off_raw_list.product_id)))
     JOIN status s ON ((s.status_id = write_off_raw_list.status_id)));


ALTER TABLE write_off_raw_list_view OWNER TO postgres;

--
-- TOC entry 471 (class 1259 OID 230066)
-- Name: write_off_raws_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW write_off_raws_view AS
 SELECT write_off_raws.write_off_raw_id,
    to_char(write_off_raws.write_off_raw_date, 'dd.MM.yyyy hh24:mi'::text) AS write_off_raw_date,
    to_char(write_off_raws.execution_date, 'dd.MM.yyyy hh24:mi'::text) AS execution_date,
    s.status_code,
    s.status_name,
    u1.user_name AS employee_name,
    u1.user_surname AS employee_surname,
    u1.user_phone AS employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u1.user_id)))) AS employee_position_name,
    u2.user_name AS stock_employee_name,
    u2.user_surname AS stock_employee_surname,
    u2.user_phone AS stock_employee_phone,
    ( SELECT positions.position_name
           FROM positions
          WHERE (positions.position_id = ( SELECT employees.position_id
                   FROM employees
                  WHERE (employees.user_id = u2.user_id)))) AS stock_employee_position_name,
    write_off_raws.count,
    write_off_raws.sum,
    c.currency_short_name AS currency_name,
    write_off_raws.employee_id,
    write_off_raws.user_id,
    write_off_raws.status_id,
    write_off_raws.currency_id
   FROM ((((write_off_raws
     LEFT JOIN users u1 ON ((u1.user_id = write_off_raws.user_id)))
     LEFT JOIN users u2 ON ((u2.user_id = write_off_raws.employee_id)))
     LEFT JOIN status s ON ((s.status_id = write_off_raws.status_id)))
     LEFT JOIN currencies c ON ((c.currency_id = write_off_raws.currency_id)));


ALTER TABLE write_off_raws_view OWNER TO postgres;

--
-- TOC entry 472 (class 1259 OID 230071)
-- Name: write_offs_view; Type: VIEW; Schema: OrmasSchema; Owner: postgres
--

CREATE VIEW write_offs_view AS
 SELECT write_offs.write_off_id,
    to_char(write_offs.write_off_date, 'dd.MM.yyyy hh24:mi'::text) AS write_off_date,
    to_char(write_offs.execution_date, 'dd.MM.yyyy hh24:mi'::text) AS execution_date,
    s.status_code,
    s.status_name,
    u1.user_name AS client_name,
    u1.user_surname AS client_surname,
    u1.user_phone AS client_phone,
    u1.user_address AS clinet_address,
    ( SELECT clients.firm
           FROM clients
          WHERE (clients.user_id = u1.user_id)) AS client_firm,
    u2.user_name AS employee_name,
    u2.user_surname AS employee_surname,
    u2.user_phone AS employee_phone,
    write_offs.count,
    write_offs.sum,
    c.currency_short_name AS currency_name,
    write_offs.employee_id,
    write_offs.user_id,
    write_offs.status_id,
    write_offs.currency_id
   FROM ((((write_offs
     LEFT JOIN users u1 ON ((u1.user_id = write_offs.user_id)))
     LEFT JOIN users u2 ON ((u2.user_id = write_offs.employee_id)))
     LEFT JOIN status s ON ((s.status_id = write_offs.status_id)))
     LEFT JOIN currencies c ON ((c.currency_id = write_offs.currency_id)));


ALTER TABLE write_offs_view OWNER TO postgres;

--
-- TOC entry 3141 (class 2606 OID 230077)
-- Name: access_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY accesses
    ADD CONSTRAINT access_pkey PRIMARY KEY (access_id);


--
-- TOC entry 3145 (class 2606 OID 230079)
-- Name: account_change_log_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY account_change_log
    ADD CONSTRAINT account_change_log_pkey PRIMARY KEY (account_change_log_id);


--
-- TOC entry 3147 (class 2606 OID 230081)
-- Name: account_history_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY account_history
    ADD CONSTRAINT account_history_pkey PRIMARY KEY (account_history_id);


--
-- TOC entry 3171 (class 2606 OID 230083)
-- Name: account_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY accounts
    ADD CONSTRAINT account_pkey PRIMARY KEY (account_id);


--
-- TOC entry 3149 (class 2606 OID 230085)
-- Name: account_type_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY account_type
    ADD CONSTRAINT account_type_pkey PRIMARY KEY (account_type_id);


--
-- TOC entry 3153 (class 2606 OID 230087)
-- Name: accountable_approvement_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY accountable_approvement
    ADD CONSTRAINT accountable_approvement_pkey PRIMARY KEY (accountable_approvement_id);


--
-- TOC entry 3155 (class 2606 OID 230089)
-- Name: accountable_document_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY accountable_document_list
    ADD CONSTRAINT accountable_document_list_pkey PRIMARY KEY (accountable_document_list_id);


--
-- TOC entry 3157 (class 2606 OID 230091)
-- Name: accountable_document_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY accountable_documents
    ADD CONSTRAINT accountable_document_pkey PRIMARY KEY (accountable_document_id);


--
-- TOC entry 3159 (class 2606 OID 230093)
-- Name: accountable_entry_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY accountable_entries
    ADD CONSTRAINT accountable_entry_pkey PRIMARY KEY (accountable_entry_id);


--
-- TOC entry 3161 (class 2606 OID 230095)
-- Name: accountable_payment_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY accountable_payment
    ADD CONSTRAINT accountable_payment_pkey PRIMARY KEY (accountable_payment_id);


--
-- TOC entry 3151 (class 2606 OID 230097)
-- Name: accountable_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY accountable
    ADD CONSTRAINT accountable_pkey PRIMARY KEY (employee_id);


--
-- TOC entry 3163 (class 2606 OID 230099)
-- Name: accountable_trancation_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY accountable_transaction
    ADD CONSTRAINT accountable_trancation_pkey PRIMARY KEY (accountable_transaction_id);


--
-- TOC entry 3167 (class 2606 OID 230101)
-- Name: accountable_withdrawal_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY accountable_withdrawal
    ADD CONSTRAINT accountable_withdrawal_pkey PRIMARY KEY (accountable_withdrawal_id);


--
-- TOC entry 3169 (class 2606 OID 230103)
-- Name: accountables_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY accountables
    ADD CONSTRAINT accountables_pkey PRIMARY KEY (accountable_id);


--
-- TOC entry 3173 (class 2606 OID 230105)
-- Name: amortize_group_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY amortize_group
    ADD CONSTRAINT amortize_group_pkey PRIMARY KEY (amortize_group_id);


--
-- TOC entry 3175 (class 2606 OID 230107)
-- Name: amortize_type_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY amortize_type
    ADD CONSTRAINT amortize_type_pkey PRIMARY KEY (amortize_type_id);


--
-- TOC entry 3177 (class 2606 OID 230109)
-- Name: balance_payment_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY balance_payment
    ADD CONSTRAINT balance_payment_pkey PRIMARY KEY (balance_payment_id);


--
-- TOC entry 3179 (class 2606 OID 230111)
-- Name: balance_payslip_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY balance_payslip
    ADD CONSTRAINT balance_payslip_pkey PRIMARY KEY (balance_payslip_id);


--
-- TOC entry 3185 (class 2606 OID 230113)
-- Name: balance_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY balances
    ADD CONSTRAINT balance_pkey PRIMARY KEY (balance_id);


--
-- TOC entry 3181 (class 2606 OID 230115)
-- Name: balance_refund_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY balance_refund
    ADD CONSTRAINT balance_refund_pkey PRIMARY KEY (balance_refund_id);


--
-- TOC entry 3183 (class 2606 OID 230117)
-- Name: balance_withdrawal_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY balance_withdrawal
    ADD CONSTRAINT balance_withdrawal_pkey PRIMARY KEY (balance_withdrawal_id);


--
-- TOC entry 3191 (class 2606 OID 230119)
-- Name: borrower_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY borrowers
    ADD CONSTRAINT borrower_pkey PRIMARY KEY (user_id);


--
-- TOC entry 3195 (class 2606 OID 230121)
-- Name: branch_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY branches
    ADD CONSTRAINT branch_pkey PRIMARY KEY (branch_id);


--
-- TOC entry 3193 (class 2606 OID 230123)
-- Name: branch_subaccount_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY branch_subaccount
    ADD CONSTRAINT branch_subaccount_pkey PRIMARY KEY (branch_subaccount_id);


--
-- TOC entry 3199 (class 2606 OID 230125)
-- Name: cashbox_employee_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY cashbox_employee
    ADD CONSTRAINT cashbox_employee_pkey PRIMARY KEY (cashbox_employee_id);


--
-- TOC entry 3197 (class 2606 OID 230127)
-- Name: cashbox_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY cashbox
    ADD CONSTRAINT cashbox_pkey PRIMARY KEY (cashbox_id);


--
-- TOC entry 3201 (class 2606 OID 230129)
-- Name: cashbox_transaction_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY cashbox_transaction
    ADD CONSTRAINT cashbox_transaction_pkey PRIMARY KEY (cashbox_transaction_id);


--
-- TOC entry 3203 (class 2606 OID 230131)
-- Name: char_of_account_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY chart_of_accounts
    ADD CONSTRAINT char_of_account_pkey PRIMARY KEY (chart_of_account_id);


--
-- TOC entry 3205 (class 2606 OID 230133)
-- Name: client_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY clients
    ADD CONSTRAINT client_pkey PRIMARY KEY (user_id);


--
-- TOC entry 3211 (class 2606 OID 230135)
-- Name: company_account_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY company_account
    ADD CONSTRAINT company_account_pkey PRIMARY KEY (company_account_id);


--
-- TOC entry 3213 (class 2606 OID 230137)
-- Name: company_employee_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY company_employee
    ADD CONSTRAINT company_employee_pkey PRIMARY KEY (company_employee_id);


--
-- TOC entry 3209 (class 2606 OID 230139)
-- Name: company_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY companies
    ADD CONSTRAINT company_pkey PRIMARY KEY (company_id);


--
-- TOC entry 3217 (class 2606 OID 230141)
-- Name: consume_other_stocks_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY consume_other_stocks_list
    ADD CONSTRAINT consume_other_stocks_list_pkey PRIMARY KEY (consume_other_stocks_list_id);


--
-- TOC entry 3215 (class 2606 OID 230143)
-- Name: consume_other_stocks_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY consume_other_stocks
    ADD CONSTRAINT consume_other_stocks_pkey PRIMARY KEY (consume_other_stocks_id);


--
-- TOC entry 3229 (class 2606 OID 230145)
-- Name: consume_product_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY consume_product_list
    ADD CONSTRAINT consume_product_list_pkey PRIMARY KEY (consume_product_list_id);


--
-- TOC entry 3233 (class 2606 OID 230147)
-- Name: consume_product_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY consume_products
    ADD CONSTRAINT consume_product_pkey PRIMARY KEY (consume_product_id);


--
-- TOC entry 3235 (class 2606 OID 230149)
-- Name: consume_raw_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY consume_raw_list
    ADD CONSTRAINT consume_raw_list_pkey PRIMARY KEY (consume_raw_list_id);


--
-- TOC entry 3237 (class 2606 OID 230151)
-- Name: consume_raw_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY consume_raws
    ADD CONSTRAINT consume_raw_pkey PRIMARY KEY (consume_raw_id);


--
-- TOC entry 3239 (class 2606 OID 230153)
-- Name: creditor_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY creditors
    ADD CONSTRAINT creditor_pkey PRIMARY KEY (creditor_id);


--
-- TOC entry 3187 (class 2606 OID 230155)
-- Name: currency_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY currencies
    ADD CONSTRAINT currency_pkey PRIMARY KEY (currency_id);


--
-- TOC entry 3241 (class 2606 OID 230157)
-- Name: division_account_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY division_account
    ADD CONSTRAINT division_account_pkey PRIMARY KEY (division_account_id);


--
-- TOC entry 3245 (class 2606 OID 230159)
-- Name: division_employee_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY division_employee
    ADD CONSTRAINT division_employee_pkey PRIMARY KEY (division_employee_id);


--
-- TOC entry 3243 (class 2606 OID 230161)
-- Name: division_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY divisions
    ADD CONSTRAINT division_pkey PRIMARY KEY (division_id);


--
-- TOC entry 3225 (class 2606 OID 230163)
-- Name: employee_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY employees
    ADD CONSTRAINT employee_pkey PRIMARY KEY (user_id);


--
-- TOC entry 3247 (class 2606 OID 230165)
-- Name: employee_product_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY employee_product
    ADD CONSTRAINT employee_product_pkey PRIMARY KEY (employee_product_id);


--
-- TOC entry 3252 (class 2606 OID 230167)
-- Name: entry_operation_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY entry_operation
    ADD CONSTRAINT entry_operation_pkey PRIMARY KEY (entry_operation_id);


--
-- TOC entry 3250 (class 2606 OID 230169)
-- Name: entry_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY entries
    ADD CONSTRAINT entry_pkey PRIMARY KEY (entry_id);


--
-- TOC entry 3288 (class 2606 OID 230171)
-- Name: entry_routing_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY entry_routing
    ADD CONSTRAINT entry_routing_pkey PRIMARY KEY (entry_routing_id);


--
-- TOC entry 3254 (class 2606 OID 230173)
-- Name: entry_subaccount_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY entry_subaccount
    ADD CONSTRAINT entry_subaccount_pkey PRIMARY KEY (entry_subaccount_id);


--
-- TOC entry 3290 (class 2606 OID 230175)
-- Name: expense_document_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY expense_document
    ADD CONSTRAINT expense_document_pkey PRIMARY KEY (expense_document_id);


--
-- TOC entry 3292 (class 2606 OID 230177)
-- Name: financial_report_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY financial_report
    ADD CONSTRAINT financial_report_pkey PRIMARY KEY (financial_report_id);


--
-- TOC entry 3294 (class 2606 OID 230179)
-- Name: fixed_assets_details_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY fixed_assets_details
    ADD CONSTRAINT fixed_assets_details_pkey PRIMARY KEY (fixed_assets_details_id);


--
-- TOC entry 3258 (class 2606 OID 230181)
-- Name: fixed_assets_operations_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY fixed_assets_operations
    ADD CONSTRAINT fixed_assets_operations_pkey PRIMARY KEY (fixed_assets_operation_id);


--
-- TOC entry 3256 (class 2606 OID 230183)
-- Name: fixed_assets_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY fixed_assets
    ADD CONSTRAINT fixed_assets_pkey PRIMARY KEY (fixed_assets_id);


--
-- TOC entry 3296 (class 2606 OID 230185)
-- Name: fixed_assets_specification_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY fixed_assets_specification
    ADD CONSTRAINT fixed_assets_specification_pkey PRIMARY KEY (fixed_assets_specification_id);


--
-- TOC entry 3300 (class 2606 OID 230187)
-- Name: group_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY groups
    ADD CONSTRAINT group_pkey PRIMARY KEY (group_id);


--
-- TOC entry 3302 (class 2606 OID 230189)
-- Name: inventorization_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY inventorization_list
    ADD CONSTRAINT inventorization_list_pkey PRIMARY KEY (inventorization_list_id);


--
-- TOC entry 3304 (class 2606 OID 230191)
-- Name: inventorization_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY inventorizations
    ADD CONSTRAINT inventorization_pkey PRIMARY KEY (inventorization_id);


--
-- TOC entry 3260 (class 2606 OID 230193)
-- Name: inventory_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY inventory
    ADD CONSTRAINT inventory_pkey PRIMARY KEY (inventory_id);


--
-- TOC entry 3306 (class 2606 OID 230195)
-- Name: inventroy_history_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY inventory_history
    ADD CONSTRAINT inventroy_history_pkey PRIMARY KEY (inventory_history_id);


--
-- TOC entry 3308 (class 2606 OID 230197)
-- Name: jobprice_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY jobprice
    ADD CONSTRAINT jobprice_pkey PRIMARY KEY (jobprice_id);


--
-- TOC entry 3310 (class 2606 OID 230199)
-- Name: jobsheet_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY jobsheet
    ADD CONSTRAINT jobsheet_pkey PRIMARY KEY (jobsheet_id);


--
-- TOC entry 3314 (class 2606 OID 230201)
-- Name: low_value_stock_change_log_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY low_value_stock_change_log
    ADD CONSTRAINT low_value_stock_change_log_pkey PRIMARY KEY (low_value_stock_change_log_id);


--
-- TOC entry 3316 (class 2606 OID 230203)
-- Name: low_value_stock_history_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY low_value_stock_history
    ADD CONSTRAINT low_value_stock_history_pkey PRIMARY KEY (low_value_stock_id);


--
-- TOC entry 3312 (class 2606 OID 230205)
-- Name: low_value_stocks_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY low_value_stock
    ADD CONSTRAINT low_value_stocks_pkey PRIMARY KEY (low_value_stock_id);


--
-- TOC entry 3219 (class 2606 OID 230207)
-- Name: measure_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY measures
    ADD CONSTRAINT measure_pkey PRIMARY KEY (measure_id);


--
-- TOC entry 3139 (class 2606 OID 230209)
-- Name: menu_item_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY access_items
    ADD CONSTRAINT menu_item_pkey PRIMARY KEY (access_item_id);


--
-- TOC entry 3320 (class 2606 OID 230211)
-- Name: net_cost_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY net_cost
    ADD CONSTRAINT net_cost_pkey PRIMARY KEY (net_cost_id);


--
-- TOC entry 3322 (class 2606 OID 230213)
-- Name: order_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY order_list
    ADD CONSTRAINT order_list_pkey PRIMARY KEY (order_list_id);


--
-- TOC entry 3264 (class 2606 OID 230215)
-- Name: order_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY orders
    ADD CONSTRAINT order_pkey PRIMARY KEY (order_id);


--
-- TOC entry 3324 (class 2606 OID 230217)
-- Name: order_raw_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY order_raw_list
    ADD CONSTRAINT order_raw_list_pkey PRIMARY KEY (order_raw_list_id);


--
-- TOC entry 3262 (class 2606 OID 230219)
-- Name: order_raw_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY order_raws
    ADD CONSTRAINT order_raw_pkey PRIMARY KEY (order_raw_id);


--
-- TOC entry 3221 (class 2606 OID 230221)
-- Name: other_stocks_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY other_stocks
    ADD CONSTRAINT other_stocks_pkey PRIMARY KEY (other_stocks_id);


--
-- TOC entry 3328 (class 2606 OID 230223)
-- Name: other_stocks_type_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY other_stocks_type
    ADD CONSTRAINT other_stocks_type_pkey PRIMARY KEY (other_stocks_type_id);


--
-- TOC entry 3330 (class 2606 OID 230225)
-- Name: payment_employee_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY payment_employee
    ADD CONSTRAINT payment_employee_pkey PRIMARY KEY (payment_employee_id);


--
-- TOC entry 3266 (class 2606 OID 230227)
-- Name: payment_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY payments
    ADD CONSTRAINT payment_pkey PRIMARY KEY (payment_id);


--
-- TOC entry 3268 (class 2606 OID 230229)
-- Name: payslip_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY payslips
    ADD CONSTRAINT payslip_pkey PRIMARY KEY (payslip_id);


--
-- TOC entry 3332 (class 2606 OID 230231)
-- Name: percent_rate_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY percent_rate
    ADD CONSTRAINT percent_rate_pkey PRIMARY KEY (percent_rate_id);


--
-- TOC entry 3334 (class 2606 OID 230233)
-- Name: photo_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY photos
    ADD CONSTRAINT photo_pkey PRIMARY KEY (photo_id);


--
-- TOC entry 3227 (class 2606 OID 230235)
-- Name: position_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY positions
    ADD CONSTRAINT position_pkey PRIMARY KEY (position_id);


--
-- TOC entry 3298 (class 2606 OID 230237)
-- Name: posting_fixed_assets_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY posting_fixed_assets
    ADD CONSTRAINT posting_fixed_assets_pkey PRIMARY KEY (posting_fixed_assets_id);


--
-- TOC entry 3336 (class 2606 OID 230239)
-- Name: price_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY prices
    ADD CONSTRAINT price_pkey PRIMARY KEY (price_id);


--
-- TOC entry 3338 (class 2606 OID 230241)
-- Name: product_branch_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY product_branch
    ADD CONSTRAINT product_branch_pkey PRIMARY KEY (product_branch_id);


--
-- TOC entry 3231 (class 2606 OID 230243)
-- Name: product_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY products
    ADD CONSTRAINT product_pkey PRIMARY KEY (product_id);


--
-- TOC entry 3340 (class 2606 OID 230245)
-- Name: product_type_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY product_type
    ADD CONSTRAINT product_type_pkey PRIMARY KEY (product_type_id);


--
-- TOC entry 3344 (class 2606 OID 230247)
-- Name: production_consume_raw_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY production_consume_raw_list
    ADD CONSTRAINT production_consume_raw_list_pkey PRIMARY KEY (consume_raw_list_id);


--
-- TOC entry 3270 (class 2606 OID 230249)
-- Name: production_consume_raw_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY production_consume_raws
    ADD CONSTRAINT production_consume_raw_pkey PRIMARY KEY (consume_raw_id);


--
-- TOC entry 3346 (class 2606 OID 230251)
-- Name: production_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY production_list
    ADD CONSTRAINT production_list_pkey PRIMARY KEY (production_list_id);


--
-- TOC entry 3342 (class 2606 OID 230253)
-- Name: production_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY production
    ADD CONSTRAINT production_pkey PRIMARY KEY (production_id);


--
-- TOC entry 3350 (class 2606 OID 230255)
-- Name: production_plan_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY production_plan_list
    ADD CONSTRAINT production_plan_list_pkey PRIMARY KEY (production_plan_list_id);


--
-- TOC entry 3348 (class 2606 OID 230257)
-- Name: production_plan_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY production_plan
    ADD CONSTRAINT production_plan_pkey PRIMARY KEY (production_plan_id);


--
-- TOC entry 3326 (class 2606 OID 230259)
-- Name: purveyor_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY purveyors
    ADD CONSTRAINT purveyor_pkey PRIMARY KEY (user_id);


--
-- TOC entry 3352 (class 2606 OID 230261)
-- Name: receipt_other_stocks_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY receipt_other_stocks_list
    ADD CONSTRAINT receipt_other_stocks_list_pkey PRIMARY KEY (receipt_other_stocks_list_id);


--
-- TOC entry 3272 (class 2606 OID 230263)
-- Name: receipt_other_stocks_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY receipt_other_stocks
    ADD CONSTRAINT receipt_other_stocks_pkey PRIMARY KEY (receipt_other_stocks_id);


--
-- TOC entry 3354 (class 2606 OID 230265)
-- Name: receipt_product_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY receipt_product_list
    ADD CONSTRAINT receipt_product_list_pkey PRIMARY KEY (receipt_product_list_id);


--
-- TOC entry 3274 (class 2606 OID 230267)
-- Name: receipt_product_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY receipt_products
    ADD CONSTRAINT receipt_product_pkey PRIMARY KEY (receipt_product_id);


--
-- TOC entry 3356 (class 2606 OID 230269)
-- Name: refund_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY refunds
    ADD CONSTRAINT refund_pkey PRIMARY KEY (refund_id);


--
-- TOC entry 3207 (class 2606 OID 230271)
-- Name: region_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY locations
    ADD CONSTRAINT region_pkey PRIMARY KEY (location_id);


--
-- TOC entry 3358 (class 2606 OID 230273)
-- Name: relarion_type_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY relation_type
    ADD CONSTRAINT relarion_type_pkey PRIMARY KEY (relation_type_id);


--
-- TOC entry 3360 (class 2606 OID 230275)
-- Name: relation_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY relations
    ADD CONSTRAINT relation_pkey PRIMARY KEY (relation_id);


--
-- TOC entry 3362 (class 2606 OID 230277)
-- Name: return_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY return_list
    ADD CONSTRAINT return_list_pkey PRIMARY KEY (return_list_id);


--
-- TOC entry 3276 (class 2606 OID 230279)
-- Name: return_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY returns
    ADD CONSTRAINT return_pkey PRIMARY KEY (return_id);


--
-- TOC entry 3143 (class 2606 OID 230281)
-- Name: role_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY roles
    ADD CONSTRAINT role_pkey PRIMARY KEY (role_id);


--
-- TOC entry 3364 (class 2606 OID 230283)
-- Name: salary_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY salaries
    ADD CONSTRAINT salary_pkey PRIMARY KEY (salary_id);


--
-- TOC entry 3366 (class 2606 OID 230285)
-- Name: salary_type_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY salary_type
    ADD CONSTRAINT salary_type_pkey PRIMARY KEY (salary_type_id);


--
-- TOC entry 3368 (class 2606 OID 230287)
-- Name: shareholder_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY shareholders
    ADD CONSTRAINT shareholder_pkey PRIMARY KEY (user_id);


--
-- TOC entry 3370 (class 2606 OID 230289)
-- Name: specification_change_log_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY specification_change_log
    ADD CONSTRAINT specification_change_log_pkey PRIMARY KEY (specification_change_log_id);


--
-- TOC entry 3372 (class 2606 OID 230291)
-- Name: specification_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY specification_list
    ADD CONSTRAINT specification_list_pkey PRIMARY KEY (specification_list_id);


--
-- TOC entry 3374 (class 2606 OID 230293)
-- Name: specification_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY specifications
    ADD CONSTRAINT specification_pkey PRIMARY KEY (specification_id);


--
-- TOC entry 3376 (class 2606 OID 230295)
-- Name: spoilage_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY spoilage_list
    ADD CONSTRAINT spoilage_list_pkey PRIMARY KEY (spoilage_list_id);


--
-- TOC entry 3278 (class 2606 OID 230297)
-- Name: spoilage_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY spoilage
    ADD CONSTRAINT spoilage_pkey PRIMARY KEY (spoilage_id);


--
-- TOC entry 3378 (class 2606 OID 230299)
-- Name: state_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY state
    ADD CONSTRAINT state_pkey PRIMARY KEY (state_id);


--
-- TOC entry 3223 (class 2606 OID 230301)
-- Name: status_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY status
    ADD CONSTRAINT status_pkey PRIMARY KEY (status_id);


--
-- TOC entry 3380 (class 2606 OID 230303)
-- Name: status_rule_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY status_rule
    ADD CONSTRAINT status_rule_pkey PRIMARY KEY (status_rule_id);


--
-- TOC entry 3384 (class 2606 OID 230305)
-- Name: stock_change_log_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY stock_change_log
    ADD CONSTRAINT stock_change_log_pkey PRIMARY KEY (stock_change_log_id);


--
-- TOC entry 3386 (class 2606 OID 230307)
-- Name: stock_history_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY stock_history
    ADD CONSTRAINT stock_history_pkey PRIMARY KEY (stock_id);


--
-- TOC entry 3388 (class 2606 OID 230309)
-- Name: stock_limit_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY stock_limit
    ADD CONSTRAINT stock_limit_pkey PRIMARY KEY (stock_limit_id);


--
-- TOC entry 3382 (class 2606 OID 230311)
-- Name: stock_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY stock
    ADD CONSTRAINT stock_pkey PRIMARY KEY (stock_id);


--
-- TOC entry 3390 (class 2606 OID 230313)
-- Name: stock_transfer_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY stock_transfer_list
    ADD CONSTRAINT stock_transfer_list_pkey PRIMARY KEY (stock_transfer_list_id);


--
-- TOC entry 3280 (class 2606 OID 230315)
-- Name: stock_transfers_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY stock_transfers
    ADD CONSTRAINT stock_transfers_pkey PRIMARY KEY (stock_transfer_id);


--
-- TOC entry 3392 (class 2606 OID 230317)
-- Name: subaccount_change_log_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY subaccount_change_log
    ADD CONSTRAINT subaccount_change_log_pkey PRIMARY KEY (subaccount_change_log_id);


--
-- TOC entry 3394 (class 2606 OID 230319)
-- Name: subaccount_history_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY subaccount_history
    ADD CONSTRAINT subaccount_history_pkey PRIMARY KEY (subaccount_history_id);


--
-- TOC entry 3396 (class 2606 OID 230321)
-- Name: subaccount_limit_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY subaccount_limit
    ADD CONSTRAINT subaccount_limit_pkey PRIMARY KEY (subaccount_id);


--
-- TOC entry 3189 (class 2606 OID 230323)
-- Name: subaccount_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY subaccounts
    ADD CONSTRAINT subaccount_pkey PRIMARY KEY (subaccount_id);


--
-- TOC entry 3398 (class 2606 OID 230325)
-- Name: tax_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY taxes
    ADD CONSTRAINT tax_pkey PRIMARY KEY (tax_id);


--
-- TOC entry 3400 (class 2606 OID 230327)
-- Name: timesheet_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY timesheet
    ADD CONSTRAINT timesheet_pkey PRIMARY KEY (timesheet_id);


--
-- TOC entry 3402 (class 2606 OID 230329)
-- Name: transport_change_log_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY transport_change_log
    ADD CONSTRAINT transport_change_log_pkey PRIMARY KEY (transport_change_log_id);


--
-- TOC entry 3404 (class 2606 OID 230331)
-- Name: transport_history_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY transport_history
    ADD CONSTRAINT transport_history_pkey PRIMARY KEY (transport_history_id);


--
-- TOC entry 3406 (class 2606 OID 230333)
-- Name: transport_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY transport_list
    ADD CONSTRAINT transport_list_pkey PRIMARY KEY (transport_list_id);


--
-- TOC entry 3408 (class 2606 OID 230335)
-- Name: transport_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY transports
    ADD CONSTRAINT transport_pkey PRIMARY KEY (transport_id);


--
-- TOC entry 3410 (class 2606 OID 230337)
-- Name: user_group_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY user_group
    ADD CONSTRAINT user_group_pkey PRIMARY KEY (user_group_id);


--
-- TOC entry 3165 (class 2606 OID 230339)
-- Name: user_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY users
    ADD CONSTRAINT user_pkey PRIMARY KEY (user_id);


--
-- TOC entry 3412 (class 2606 OID 230341)
-- Name: warehouse_employee_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY warehouse_employee
    ADD CONSTRAINT warehouse_employee_pkey PRIMARY KEY (warehouse_employee_id);


--
-- TOC entry 3318 (class 2606 OID 230343)
-- Name: warehouse_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY warehouse
    ADD CONSTRAINT warehouse_pkey PRIMARY KEY (warehouse_id);


--
-- TOC entry 3414 (class 2606 OID 230345)
-- Name: warehouse_type_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY warehouse_type
    ADD CONSTRAINT warehouse_type_pkey PRIMARY KEY (warehouse_type_id);


--
-- TOC entry 3284 (class 2606 OID 230347)
-- Name: wite_off_raw_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY write_off_raws
    ADD CONSTRAINT wite_off_raw_pkey PRIMARY KEY (write_off_raw_id);


--
-- TOC entry 3282 (class 2606 OID 230349)
-- Name: withdrawal_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY withdrawals
    ADD CONSTRAINT withdrawal_pkey PRIMARY KEY (withdrawal_id);


--
-- TOC entry 3416 (class 2606 OID 230351)
-- Name: write_off_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY write_off_list
    ADD CONSTRAINT write_off_list_pkey PRIMARY KEY (write_off_list_id);


--
-- TOC entry 3286 (class 2606 OID 230353)
-- Name: write_off_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY write_offs
    ADD CONSTRAINT write_off_pkey PRIMARY KEY (write_off_id);


--
-- TOC entry 3418 (class 2606 OID 230355)
-- Name: write_off_raw_list_pkey; Type: CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY write_off_raw_list
    ADD CONSTRAINT write_off_raw_list_pkey PRIMARY KEY (write_off_raw_list_id);


--
-- TOC entry 3248 (class 1259 OID 230356)
-- Name: entry_date_index; Type: INDEX; Schema: OrmasSchema; Owner: postgres
--

CREATE INDEX entry_date_index ON "OrmasSchema".entries USING btree (entry_date DESC);


--
-- TOC entry 3419 (class 2606 OID 230357)
-- Name: access_fkey; Type: FK CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY accesses
    ADD CONSTRAINT access_fkey FOREIGN KEY (access_item_id) REFERENCES access_items(access_item_id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 3420 (class 2606 OID 230362)
-- Name: balance_subaccount_fkey; Type: FK CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY balances
    ADD CONSTRAINT balance_subaccount_fkey FOREIGN KEY (subaccount_id) REFERENCES subaccounts(subaccount_id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 3421 (class 2606 OID 230367)
-- Name: balance_user_fkey; Type: FK CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY balances
    ADD CONSTRAINT balance_user_fkey FOREIGN KEY (user_id) REFERENCES users(user_id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 3422 (class 2606 OID 230372)
-- Name: client_fkey; Type: FK CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY clients
    ADD CONSTRAINT client_fkey FOREIGN KEY (user_id) REFERENCES users(user_id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 3423 (class 2606 OID 230377)
-- Name: employee_fkey; Type: FK CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY employees
    ADD CONSTRAINT employee_fkey FOREIGN KEY (user_id) REFERENCES users(user_id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 3424 (class 2606 OID 230382)
-- Name: purveyor_fkey; Type: FK CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY purveyors
    ADD CONSTRAINT purveyor_fkey FOREIGN KEY (user_id) REFERENCES users(user_id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 3425 (class 2606 OID 230387)
-- Name: salary_fkey; Type: FK CONSTRAINT; Schema: OrmasSchema; Owner: postgres
--

ALTER TABLE ONLY salaries
    ADD CONSTRAINT salary_fkey FOREIGN KEY (user_id) REFERENCES users(user_id);


--
-- TOC entry 3693 (class 0 OID 0)
-- Dependencies: 7
-- Name: OrmasSchema; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA "OrmasSchema" FROM PUBLIC;
REVOKE ALL ON SCHEMA "OrmasSchema" FROM postgres;
GRANT ALL ON SCHEMA "OrmasSchema" TO postgres;
GRANT ALL ON SCHEMA "OrmasSchema" TO PUBLIC;


--
-- TOC entry 3695 (class 0 OID 0)
-- Dependencies: 8
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


-- Completed on 2022-04-17 15:31:53

--
-- PostgreSQL database dump complete
--

