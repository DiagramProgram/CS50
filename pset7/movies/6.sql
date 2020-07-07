--SELECT AVG(ratings.rating) from ratings, movies WHERE movies.year = 2012;

SELECT AVG(rating)
FROM ratings
WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012);