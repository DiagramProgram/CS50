SELECT people.name FROM people WHERE people.name != "Kevin Bacon"
AND people.id IN
    (SELECT person_id FROM stars WHERE movie_id IN
        (SELECT id FROM movies WHERE id IN
            (SELECT movie_id FROM stars WHERE person_id IN
                (SELECT id FROM people WHERE people.name = "Kevin Bacon" AND people.birth = 1958))));


/*JOIN movies ON movies.id = stars.movie_id
JOIN stars ON people.id = stars.person_id
WHERE people.name IN ("Kevin Bacon");*/