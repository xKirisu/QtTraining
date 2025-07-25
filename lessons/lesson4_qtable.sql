-- Table: public.qtable

-- DROP TABLE IF EXISTS public.qtable;

CREATE TABLE IF NOT EXISTS public.qtable
(
    id integer NOT NULL DEFAULT nextval('qtable_id_seq'::regclass),
    name character varying COLLATE pg_catalog."default",
    code integer,
    color character varying(8) COLLATE pg_catalog."default",
    date date,
    square_area integer,
    CONSTRAINT qtable_pkey PRIMARY KEY (id)
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.qtable
    OWNER to postgres;