SELECT people.name FROM people
JOIN movies ON movies.id = directors.movie_id
JOIN directors ON directors.person_id = people.id
JOIN ratings ON ratings.movie_id = movies.id
WHERE ratings.rating >= 9;