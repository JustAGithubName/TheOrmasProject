INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0001', 'SUCCESS', 'Any operations which ends with success');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0002', 'FAIL', 'Any operations which ends with fail');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0003', 'IN PROGRESS', 'In progress status is informed that operation is realizing');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0004', 'DONE', 'Any action is done');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0005', 'EXECUTED', 'Execution status is shown that employee done his job');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0006', 'ERROR', 'Operation or action was ended with error');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0007', 'ORDERED', 'Status of ordering');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0008', 'TO RETURN', 'Status of ordering');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0009', 'WRITE-OFFED', 'Status of ordering');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0010', 'PRODUCED', 'Status of product production');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0011', 'IN STOCK', 'Status of product production');
	INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0012', 'TRANSPORTING', 'Products are transporting');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0013', 'TRANSPORTED', 'Products were transported');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0014', 'CONSUMED', 'Products/Raws were consumed');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0015', 'RECEIPTED', 'Products/Raws were receipted');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0016', 'INVENTORIZED', 'Inventorization of stock');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0017', 'STOKED', 'Products are stoked');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0018', 'OPEN', 'Account status is opened');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0019', 'CLOSED', 'Account status is closed');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0020', 'PLANNED', 'Production is planed');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0021', 'SPOILAGE', 'Product is spoilage');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0022', 'TO PAY', 'To pay');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0023', 'RETURN', 'Return');
INSERT INTO "OrmasSchema".status(
            status_id, status_code, status_name, comment)
    VALUES ((SELECT nextval('"OrmasSchema".id_seq')), '0024', 'IN USE', 'In use');