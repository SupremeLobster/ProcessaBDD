/* COUNT ROUTES - Crec que així funcionaria a SQL*/
SELECT t1.NAT AS "NAT.", t2.INTL AS "INTL.", t1.NAME AS AIRLINE
	FROM (SELECT al.name AS NAME, COUNT(*) AS NAT
			FROM airlines al
				JOIN routes r
					ON al.id = r.air_id
				JOIN airports ap1
					ON r.source_id = ap1.id
				JOIN airports ap2
					ON r.dest_id = ap2.id
			GROUP BY al.name
			HAVING al.country = ap1.country AND al.country = ap2.country
		 ) t1
		JOIN (SELECT al.name AS NAME, COUNT(*) AS INTL
				FROM airlines al
					JOIN routes r
						ON al.id = r.air_id
					JOIN airports ap1
						ON r.source_id = ap1.id
					JOIN airports ap2
						ON r.dest_id = ap2.id
				GROUP BY al.name
				HAVING al.country != ap1.country OR al.country != ap2.country
			 ) t2
			ON t1.name = t2.name;